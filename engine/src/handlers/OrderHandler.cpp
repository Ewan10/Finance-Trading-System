#include "handlers/OrderHandler.h"
#include <nlohmann/json.hpp>

namespace Exchange
{
    std::string OrderHandler::handleAddOrder(Order &order)
    {
        engine.submitOrder(order);
        return makeStatus("added");
    }

    std::string OrderHandler::handleCancelOrder(uint64_t orderId)
    {
        engine.cancelOrder(orderId);
        return makeStatus("cancelled");
    }

    std::string OrderHandler::handleModifyOrder(uint64_t orderId, const nlohmann::json &body)
    {
        engine.modifyOrder(orderId, body["price"], body["quantity"]);
        return makeStatus("modified");
    }

    std::string OrderHandler::handleGetBook()
    {
        auto book = engine.getOrderBookSnapshot();

        nlohmann::json data;
        data["bids"] = book["bids"];
        data["asks"] = book["asks"];
        return makeDataResponse(data);
    }

    std::string OrderHandler::handleGetTrades()
    {
        auto trades = engine.getTrades();
        nlohmann::json data;
        data["trades"] = trades;
        return makeDataResponse(data);
    }

    std::string OrderHandler::makeStatus(const std::string &status)
    {
        nlohmann::json res;
        res["status"] = status;
        return res.dump();
    }

    std::string OrderHandler::makeDataResponse(const nlohmann::json &data)
    {
        nlohmann::json res;
        res["status"] = "ok";
        res["data"] = data;
        return res.dump();
    }
}