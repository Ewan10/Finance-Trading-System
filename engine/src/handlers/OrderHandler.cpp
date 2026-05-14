#include "handlers/OrderHandler.h"
#include <nlohmann/json.hpp>
#include "utils/time_utils.hpp"

namespace Exchange
{
    std::string OrderHandler::handleAddOrder(Order &order)
    {
        engine.submitOrder(order);
        nlohmann::json res;
        res["orderId"] = order.getOrderId();
        res["clientId"] = order.getClientId();
        res["side"] = Order::sideToString(order.getSide());
        res["quantity"] = order.getQuantity();
        res["price"] = order.getPrice();
        res["timestamp"] = utils::toISO8601(order.getTimestamp());
        res["status"] = Order::statusToString(order.status);
        return res.dump();
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