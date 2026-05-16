#pragma once
#include "core/types/Order.h"
#include "core/types/Trade.h"
#include <map>
#include <unordered_map>
#include <list>
#include <nlohmann/json.hpp>
#include <iostream>

namespace Exchange
{
    class LimitOrderBook
    {
    private:
        std::map<uint64_t, std::list<Order>, std::greater<>> bids;
        std::map<uint64_t, std::list<Order>> asks;
        std::vector<Trade> trades;
        std::unordered_map<uint64_t, std::list<Order>::iterator> orderIndex;

        void sortBids();
        void sortAsks();
        void matchBuyOrder(Order &order);
        void matchSellOrder(Order &order);
        template <typename Book>
        void removeOrderFromBook(Book &book, std::list<Order>::iterator listIt, uint64_t price);
        void removeEmptyBidLevel(uint64_t price);
        void removeEmptyAskLevel(uint64_t price);
        template <typename Book, typename PriceCondition>
        void match(Order &order, Book &book, PriceCondition priceMatch);

    public:
        enum class OrderResult
        {
            ACCEPTED,
            REJECTED_DUPLICATE,
            REJECTED_INVALID
        };
        LimitOrderBook::OrderResult addOrder(Order &order);
        std::optional<std::pair<uint64_t, uint64_t>> getBestBid() const;
        std::optional<std::pair<uint64_t, uint64_t>> getBestAsk() const;
        nlohmann::json getOrderBookSnapshot() const;
        void printOrderBook() const;
        void printTrades() const;
        const std::vector<Trade>& getTrades();
        void cancelOrder(uint64_t orderId);
        void modifyOrder(uint64_t orderId, uint64_t newPrice, uint64_t newQuantity);
        std::vector<Trade> drainTrades();
        void addBid(const Order &order);
        void addAsk(const Order &order);
    };
}

template <typename Book, typename PriceCondition>
void Exchange::LimitOrderBook::match(Order &order, Book &book, PriceCondition priceMatch)
{
    while (!book.empty() && !order.isFilled())
    {
        auto it = book.begin();
        uint64_t bestPrice = it->first;

        if (!priceMatch(bestPrice, order.getPrice()))
        {
            break;
        }

        auto &orders = it->second;

        while (!orders.empty() && !order.isFilled())
        {
            auto &restingOrder = orders.front();

            uint64_t tradedQuantity = std::min(
                order.getRemainingQuantity(),
                restingOrder.getRemainingQuantity());
            std::cout << "Traded quantity: " << tradedQuantity << "\n";

            uint64_t buyId, sellId;

            if (order.getSide() == Order::Side::BUY)
            {
                buyId = order.getOrderId();
                sellId = restingOrder.getOrderId();
            }
            else
            {
                buyId = restingOrder.getOrderId();
                sellId = order.getOrderId();
            }

            uint64_t tradePrice = restingOrder.getPrice();

            trades.emplace_back(
                Trade::generateTradeId(),
                (order.getSide() == Order::Side::BUY ? order.getOrderId() : restingOrder.getOrderId()),
                (order.getSide() == Order::Side::SELL ? order.getOrderId() : restingOrder.getOrderId()),
                tradePrice,
                tradedQuantity,
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count());

            order.setRemainingQuantity(
                order.getRemainingQuantity() - tradedQuantity);
            restingOrder.setRemainingQuantity(
                restingOrder.getRemainingQuantity() - tradedQuantity);

            if (restingOrder.isFilled())
            {
                restingOrder.setStatus(Order::Status::FILLED);
                orderIndex.erase(restingOrder.getOrderId());
                orders.pop_front();
            }
            else
            {
                restingOrder.setStatus(Order::Status::PARTIALLY_FILLED);
            }
        }

        if (orders.empty())
        {
            book.erase(it);
        }
    }
}