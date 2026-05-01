#pragma once
#include <cstdint>
#include "core/limitOrderBook/LimitOrderBook.h"
#include "core/types/Trade.h"
#include <vector>

namespace Exchange
{
    class MatchingEngine
    {
        private:
            LimitOrderBook orderBook;

        public:
            MatchingEngine() = default;

            void submitOrder(Order& order);
            void cancelOrder(uint64_t orderId);
            void modifyOrder(uint64_t orderId, uint64_t newPrice, uint64_t newQuantity );

            std::optional<std::pair<uint64_t, uint64_t>> getBestBid() const;
            std::optional<std::pair<uint64_t, uint64_t>> getBestAsk() const;
            
            const std::vector<Trade>& getTrades();
            nlohmann::json getOrderBookSnapshot() const;
            void printOrderBook() const;
           void printTrades() const;

            // void resetEngine();
    };
}