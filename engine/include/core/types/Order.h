#pragma once
#include <cstdint>
#include <chrono>
#include <stdexcept>

namespace Exchange {

    class Order {
        private:
        uint64_t orderId;
        uint64_t clientId;
        std::chrono::steady_clock::time_point timestamp;
        uint64_t price;
        uint64_t quantity;
        uint64_t remainingQuantity;
        
        public:
        enum class Status { NEW, PARTIALLY_FILLED, FILLED, CANCELLED } status;
        enum class Side { BUY, SELL } side;
            Order(uint64_t orderId, uint64_t clientId, std::chrono::steady_clock::time_point timestamp,
                uint64_t price, uint64_t quantity, Side side);
            void fill(uint64_t fillQuantity);
            bool isFilled() const;
            void cancel();
            void reduceQuantity(uint64_t amount) {
                if (amount > remainingQuantity) {
                    throw std::runtime_error("Overfill error");
                }
                remainingQuantity -= amount;
            }
            Side getSide() const { return side; };
            uint64_t getPrice() const { return price; };
            uint64_t getOrderId() const{ return orderId; };
            void setPrice(uint64_t newPrice) { price = newPrice; };
            uint64_t getRemainingQuantity() const { return remainingQuantity; };
            uint64_t setRemainingQuantity(uint64_t newRemainingQuantity) { remainingQuantity = newRemainingQuantity; return remainingQuantity; };
            void setStatus(Status newStatus) { status = newStatus; };

    };

}