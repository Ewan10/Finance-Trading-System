#include "api/HttpServer.h"

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include "core/types/Order.h"
#include "handlers/OrderHandler.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace Exchange
{
    // ---------------- Constructor ----------------

    HttpServer::HttpServer(net::io_context &ioc, unsigned short port, OrderHandler& handler)
        : ioc_(ioc),
          acceptor_(ioc, tcp::endpoint(tcp::v4(), port)),
          port_(port),
          handler_(handler),
          running_(false) {}

    // ---------------- Public API ----------------

    void HttpServer::run()
    {
        running_ = true;
        do_accept();
    }

    void HttpServer::stop()
    {
        running_ = false;
        beast::error_code ec;
        acceptor_.close(ec);
    }

    // ---------------- Internal ----------------

    void HttpServer::do_accept()
    {
        acceptor_.async_accept(
            [this](beast::error_code ec, tcp::socket socket)
            {
                on_accept(ec);

                if (!ec)
                {
                    try
                    {
                        beast::flat_buffer buffer;

                        http::request<http::string_body> req;
                        http::read(socket, buffer, req);

                        http::response<http::string_body> res{
                            http::status::ok, req.version()};

                        res.set(http::field::server, "C++ Beast Server");
                        res.set(http::field::content_type, "application/json");

                        std::string target = std::string(req.target());

                        if (req.method() == http::verb::post && target == "/orders")
                        {
                            auto json = nlohmann::json::parse(req.body());
                            uint64_t orderId = json["orderId"];
                            uint64_t clientId = json["clientId"];
                            uint64_t price = json["price"];
                            uint64_t quantity = json["quantity"];
                            std::string sideStr = json["side"];

                            Order::Side side = (sideStr == "BUY") ? Order::Side::BUY : Order::Side::SELL;

                            auto timestamp = std::chrono::steady_clock::now();

                            Order order(orderId, clientId, timestamp, price, quantity, side);
                            res.body() = handler_.handleAddOrder(order);
                        }
                        else if (req.method() == http::verb::delete_ && target.rfind("/orders/", 0) == 0)
                        {
                            std::string idStr = target.substr(std::string("/orders/").size());
                            uint64_t orderId = std::stoull(idStr);
                            res.body() = handler_.handleCancelOrder(orderId);
                        }
                        else if (req.method() == http::verb::put && target.rfind("/orders/", 0) == 0)
                        {
                            std::string idStr = target.substr(std::string("/orders/").size());
                            uint64_t orderId = std::stoull(idStr);

                            auto json = nlohmann::json::parse(req.body());
                            res.body() = handler_.handleModifyOrder(orderId, json);
                        }
                        else if (req.method() == http::verb::get && target == "/orderbook")
                        {
                            res.body() = handler_.handleGetBook();
                        }
                        else if (req.method() == http::verb::get && target == "/trades")
                        {
                            res.body() = handler_.handleGetTrades();
                        }
                        else
                        {
                            res.result(http::status::not_found);
                            res.body() = "Not Found";
                        }

                        res.prepare_payload();

                        http::write(socket, res);

                        socket.shutdown(tcp::socket::shutdown_send);
                    }
                    catch (std::exception &e)
                    {
                        std::cerr << "Session error: " << e.what() << std::endl;
                    }
                }

                if (running_)
                {
                    do_accept();
                }
            });
    }

    void HttpServer::on_accept(boost::system::error_code ec)
    {
        if (ec)
        {
            std::cerr << "Accept error: " << ec.message() << std::endl;
        }
    }
}