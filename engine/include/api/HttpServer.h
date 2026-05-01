#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>
#include "handlers/OrderHandler.h"

namespace Exchange {
    class HttpServer {
    public:
        HttpServer(boost::asio::io_context& ioc, unsigned short port, OrderHandler& handler);

        // Starts listening for incoming HTTP connections
        void run();

        // Stops the server gracefully
        void stop();

    private:
        // Internal accept loop
        void do_accept();

        // Handle a single connection/session
        void on_accept(boost::system::error_code ec);

    private:
        boost::asio::io_context& ioc_;
        boost::asio::ip::tcp::acceptor acceptor_;
        unsigned short port_;
        bool running_;
        OrderHandler& handler_;
    };
}