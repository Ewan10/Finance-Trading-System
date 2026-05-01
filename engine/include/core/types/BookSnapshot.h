#pragma once
#include <vector>
#include <cstdint>
#include <nlohmann/json.hpp>

namespace Exchange
{
    struct PriceLevel
    {
        uint64_t price;
        uint64_t quantity;
    };

    struct BookSnapshot
    {
        std::vector<PriceLevel> bids;
        std::vector<PriceLevel> asks;
    };
    
}

namespace nlohmann {

    template<>
    struct adl_serializer<Exchange::PriceLevel> {
        static void to_json(json& j, const Exchange::PriceLevel& pLevel) {
            j = json {
                {"price", pLevel.price},
                {"quantity", pLevel.quantity}
            };
        }
    };

    template<>
    struct adl_serializer<Exchange::BookSnapshot> {
        static void to_json(json& j, const Exchange::BookSnapshot& snapshot) {
            j = json {
                {"bids", snapshot.bids},
                {"asks", snapshot.asks}
            };
        }
    };

}