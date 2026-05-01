#include "core/limitOrderBook/LimitOrderBook.h"
#include <cstdint>
#include <utility>
#include <algorithm>
#include "core/types/BookSnapshot.h"
#include <iostream>

namespace Exchange
{
    LimitOrderBook::OrderResult LimitOrderBook::addOrder(Order &order)
    {
        if (orderIndex.find(order.getOrderId()) != orderIndex.end())
        {
            return LimitOrderBook::OrderResult::REJECTED_DUPLICATE;
        }

        if (order.getSide() == Order::Side::BUY)
        {
            matchBuyOrder(order);
        }
        else if (order.getSide() == Order::Side::SELL)
        {
            matchSellOrder(order);
        }
        else
        {
            return LimitOrderBook::OrderResult::REJECTED_INVALID;
        }

        if (order.isFilled())
        {
            return LimitOrderBook::OrderResult::ACCEPTED;
        }

        uint64_t price = order.getPrice();

        if (order.getSide() == Order::Side::BUY)
        {
            auto &list = bids[price];
            list.push_back(order);
            auto it = std::prev(list.end());
            orderIndex[it->getOrderId()] = it;
        }
        else if (order.getSide() == Order::Side::SELL)
        {
            auto &list = asks[price];
            list.push_back(order);
            auto it = std::prev(list.end());
            orderIndex[it->getOrderId()] = it;
        }

        return LimitOrderBook::OrderResult::ACCEPTED;
    }

    void LimitOrderBook::addBid(const Order &order)
    {
        bids[order.getPrice()].push_back(order);
    }

    void LimitOrderBook::addAsk(const Order &order)
    {
        asks[order.getPrice()].push_back(order);
    }

    void LimitOrderBook::cancelOrder(uint64_t orderId)
    {
        auto it = orderIndex.find(orderId);
        if (it == orderIndex.end())
            return;

        auto orderIt = it->second;
        Order &order = *orderIt;
        uint64_t price = order.getPrice();

        if (order.getSide() == Order::Side::BUY)
        {
            removeOrderFromBook(bids, orderIt, price);
        }
        else
        {
            removeOrderFromBook(asks, orderIt, price);
        }
        orderIndex.erase(orderId);
    }

    template <typename Book>
    void LimitOrderBook::removeOrderFromBook(Book &book,
                                             std::list<Order>::iterator listIt, uint64_t price)
    {
        auto levelIt = book.find(price);
        if (levelIt == book.end())
            return;

        auto &orders = levelIt->second;
        listIt->cancel();
        orders.erase(listIt);

        if (orders.empty())
        {
            book.erase(levelIt);
        }
    }

    void LimitOrderBook::modifyOrder(uint64_t orderId, uint64_t newPrice, uint64_t newQuantity)
    {
        // 1. Early cancel check
        if (newQuantity == 0)
        {
            cancelOrder(orderId);
            return;
        }

        // 2. Lookup
        auto it = orderIndex.find(orderId);
        if (it == orderIndex.end())
            return;

        auto orderIt = it->second;
        Order &order = *orderIt;

        uint64_t oldPrice = order.getPrice();
        auto side = order.getSide();

        // 3. Quantity-only update (fast path)
        if (newPrice == oldPrice)
        {
            order.setRemainingQuantity(newQuantity);
            return;
        }

        // 4. Price change → remove from old level
        if (side == Order::Side::BUY)
        {
            removeOrderFromBook(bids, orderIt, oldPrice);
        }
        else
        {
            removeOrderFromBook(asks, orderIt, oldPrice);
        }

        // 5. Update order fields
        order.setPrice(newPrice);
        order.setRemainingQuantity(newQuantity);

        // 6. Reinsert into new level
        if (side == Order::Side::BUY)
        {
            auto &orders = bids[newPrice];
            orders.push_back(order);
            orderIndex[orderId] = std::prev(orders.end());
        }
        else
        {
            auto &orders = asks[newPrice];
            orders.push_back(order);
            orderIndex[orderId] = std::prev(orders.end());
        }
    }

    void LimitOrderBook::matchBuyOrder(Order &order)
    {
        auto buyMatchRule = [](uint64_t bookPrice, uint64_t orderPrice)
        {
            return bookPrice <= orderPrice;
        };
        match(order, asks, buyMatchRule);
    }

    void LimitOrderBook::matchSellOrder(Order &order)
    {
        auto sellMatchRule = [](uint64_t bookPrice, uint64_t orderPrice)
        {
            return bookPrice >= orderPrice;
        };
        match(order, bids, sellMatchRule);
    }

    std::optional<std::pair<uint64_t, uint64_t>> LimitOrderBook::getBestBid() const
    {
        if (bids.empty())
            return std::nullopt;

        const auto &[price, orders] = *bids.begin();
        uint64_t totalQuantity = 0;

        for (const auto &order : orders)
        {
            totalQuantity += order.getRemainingQuantity();
        }
        return std::make_pair(price, totalQuantity);
    }

    std::optional<std::pair<uint64_t, uint64_t>> LimitOrderBook::getBestAsk() const
    {
        if (asks.empty())
            return std::nullopt;

        const auto &[price, orders] = *asks.begin();
        uint64_t totalQuantity = 0;

        for (const auto &order : orders)
        {
            totalQuantity += order.getRemainingQuantity();
        }
        return std::make_pair(price, totalQuantity);
    }

     const std::vector<Trade>& LimitOrderBook::getTrades()
    {
        return trades;
    }

    nlohmann::json LimitOrderBook::getOrderBookSnapshot() const
    {
        BookSnapshot snapshot;

        for (const auto &[price, orders] : asks)
        {
            uint64_t totalQuantity = 0;

            for (const auto &order : orders)
            {
                totalQuantity += order.getRemainingQuantity();
            }
            snapshot.asks.push_back({price, totalQuantity});
        }

        for (auto it = bids.rbegin(); it != bids.rend(); ++it)
        {
            uint64_t price = it->first;
            const auto &orders = it->second;
            uint64_t totalQuantity = 0;

            for (const auto &order : orders)
            {
                totalQuantity += order.getRemainingQuantity();
            }
            snapshot.bids.push_back({price, totalQuantity});
        }

        return nlohmann::json(snapshot);
    }

    void LimitOrderBook::printOrderBook() const
    {
        std::cout << "----- ASKS -----\n";
        if (asks.empty())
        {
            std::cout << "0\n";
        }
        else
        {
            for (const auto &[price, orders] : asks)
            {
                uint64_t totalQty = 0;

                for (const auto &order : orders)
                    totalQty += order.getRemainingQuantity();

                std::cout << price << " | " << totalQty << "\n";
            }
        }

        std::cout << "----- BIDS -----\n";
        if (bids.empty())
        {
            std::cout << "0\n";
        }
        else
        {
            for (auto it = bids.rbegin(); it != bids.rend(); ++it)
            {
                uint64_t totalQty = 0;

                for (const auto &order : it->second)
                    totalQty += order.getRemainingQuantity();

                std::cout << it->first << " | " << totalQty << "\n";
            }
        }
    }

        void LimitOrderBook::printTrades() const
        {
            std::cout << "----- TRADES -----\n";

            for (const auto &trade : trades)
            {
                std::cout << "BuyID: " << trade.buyOrderId << " SellID: " << trade.sellOrderId
                          << " Price: " << trade.price << " Quantity: " << trade.quantity
                          << " Time: " << trade.timestamp << "\n";
            }
        }
    }
