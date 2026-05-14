#pragma once

#include <atomic>
#include <cstdint>

class OrderIdGenerator
{
private:
    inline static std::atomic<uint64_t> currentId = 1;

public:
    static uint64_t next()
    {
        return currentId++;
    }
};