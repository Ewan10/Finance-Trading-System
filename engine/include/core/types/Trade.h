#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <atomic>

namespace Exchange
{
    class Trade
    {
    public:
        uint64_t tradeId;
        uint64_t buyOrderId;
        uint64_t sellOrderId;
        uint64_t price;
        uint64_t quantity;
        uint64_t timestamp;

        Trade(
            uint64_t tradeId,
            uint64_t buyId,
            uint64_t sellId,
            uint64_t price,
            uint64_t qty,
            uint64_t timestamp)
            : tradeId(tradeId),
              buyOrderId(buyId),
              sellOrderId(sellId),
              price(price),
              quantity(qty),
              timestamp(timestamp) {}

        static uint64_t generateTradeId()
        {
            static std::atomic<uint64_t> counter{1};
            return counter.fetch_add(1, std::memory_order_relaxed);
        }
    };

    inline void to_json(nlohmann::json &j, const Trade &t)
    {
        j = nlohmann::json{
            {"tradeId", t.tradeId},
            {"buyOrderId", t.buyOrderId},
            {"sellOrderId", t.sellOrderId},
            {"price", t.price},
            {"quantity", t.quantity},
            {"timestamp", t.timestamp}};
    }
}