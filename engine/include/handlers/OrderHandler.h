#pragma once

#include "../core/types/Order.h"
#include <string>
#include "../core/matching-engine/MatchingEngine.h"
#include "../core/types/Trade.h"

namespace Exchange
{
    class OrderHandler
    {
        private:
    MatchingEngine& engine;
    std::string makeStatus(const std::string &status);
     std::string makeDataResponse(const nlohmann::json &data);
    public:
        OrderHandler(MatchingEngine& engine) : engine(engine) {}
        std::string handleAddOrder(Order &order);
        std::string handleCancelOrder(uint64_t orderId);
        std::string handleModifyOrder(uint64_t orderId, const nlohmann::json &body);
        std::string handleGetBook();
        std::string handleGetTrades();
    };
}