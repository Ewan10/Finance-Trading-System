#pragma once

#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

namespace utils
{
    inline std::string toISO8601(std::chrono::system_clock::time_point tp)
    {
        auto time_t = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = *std::gmtime(&time_t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        return oss.str();
    }

}