#include "core/matching-engine/MatchingEngine.h"

namespace Exchange
{
        void MatchingEngine::submitOrder(Order& order)
        {
            std::cout << "Submitting order: " << order.getOrderId() << std::endl;
            orderBook.addOrder(order);
        }

        void MatchingEngine::cancelOrder(uint64_t orderId)
        {
            orderBook.cancelOrder(orderId);
        }

        void MatchingEngine::modifyOrder(uint64_t orderId, uint64_t newPrice, uint64_t newQuantity)
        {
            orderBook.modifyOrder(orderId, newPrice, newQuantity);
        }

        std::optional<std::pair<uint64_t, uint64_t>> MatchingEngine::getBestBid() const
        {
            return orderBook.getBestBid();
        }

        std::optional<std::pair<uint64_t, uint64_t>> MatchingEngine::getBestAsk() const
        {
            return orderBook.getBestAsk();
        }

        const std::vector<Trade>& MatchingEngine::getTrades()
        {
            return orderBook.getTrades();
        }

        nlohmann::json MatchingEngine::getOrderBookSnapshot() const
        {
            return orderBook.getOrderBookSnapshot();
        }

        void MatchingEngine::printOrderBook() const
        {
            orderBook.printOrderBook();
        }

        void MatchingEngine::printTrades() const
        {
            orderBook.printTrades();
        }

}