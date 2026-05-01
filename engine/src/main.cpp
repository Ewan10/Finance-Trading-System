#include <iostream>
#include "api/HttpServer.h"
#include <boost/asio.hpp>
#include "core/matching-engine/MatchingEngine.h"
#include "core/types/Order.h"
#include "handlers/OrderHandler.h"

int main()
{
    // Exchange::MatchingEngine engine;

    // Exchange::Order o1(4, 1, std::chrono::steady_clock::now(), 100, 10, Exchange::Order::Side::BUY);
    // Exchange::Order o2(5, 1, std::chrono::steady_clock::now(), 90, 5, Exchange::Order::Side::SELL);
    // Exchange::Order o3(6, 1, std::chrono::steady_clock::now(), 95, 10, Exchange::Order::Side::SELL);

    // engine.submitOrder(o1);
    // engine.submitOrder(o2);
    // engine.submitOrder(o3);

    // engine.printOrderBook();
    // engine.printTrades();

    boost::asio::io_context ioc;
    Exchange::MatchingEngine engine;

    Exchange::OrderHandler handler(engine);

    Exchange::HttpServer server(ioc, 8081, handler);
    server.run();

    ioc.run();

    // std::cout << "Trading System Initialized (C++23)" << std::endl;
    return 0;
}