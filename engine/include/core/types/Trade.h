#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>

namespace Exchange
{
    class Trade
    {
    public:
        uint64_t buyOrderId;
        uint64_t sellOrderId;
        uint64_t price;
        uint64_t quantity;
        uint64_t timestamp;

        Trade(uint64_t buyId,
              uint64_t sellId,
              uint64_t price,
              uint64_t qty,
              uint64_t timestamp)
            : buyOrderId(buyId),
              sellOrderId(sellId),
              price(price),
              quantity(qty),
              timestamp(timestamp) {}
    };

    inline void to_json(nlohmann::json &j, const Trade &t)
    {
        j = nlohmann::json{
            {"buyOrderId", t.buyOrderId},
            {"sellOrderId", t.sellOrderId},
            {"price", t.price},
            {"quantity", t.quantity},
            {"timestamp", t.timestamp}};
    }
}