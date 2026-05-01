#include "core/types/Order.h"

namespace Exchange {
    Order::Order(uint64_t orderId, uint64_t clientId, std::chrono::steady_clock::time_point timestamp,
            uint64_t price, uint64_t quantity, Side side)
            : orderId(orderId), clientId(clientId), timestamp(timestamp), price(price),
            quantity(quantity), remainingQuantity(quantity), side(side), status(Status::NEW) {}

        void Order::fill(uint64_t fillQuantity) {
            if (status == Status::CANCELLED || status == Status::FILLED) {
                return; 
            }
            if (fillQuantity > remainingQuantity) {
                fillQuantity = remainingQuantity; 
            }
            remainingQuantity -= fillQuantity;

            if (remainingQuantity == 0) {
                status = Status::FILLED;
            } else {
                status = Status::PARTIALLY_FILLED;
            }
        }

        bool Order::isFilled() const {
            return remainingQuantity == 0;
        }

        void Order::cancel() {
            if (status == Status::FILLED || status == Status::CANCELLED) {
                return; 
            }
            status = Status::CANCELLED;
        }
}