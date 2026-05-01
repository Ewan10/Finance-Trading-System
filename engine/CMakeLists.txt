cmake_minimum_required(VERSION 3.20)

project(TradingSystem CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(TradingSystem ${SOURCES})
target_include_directories(TradingSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    C:/dev/boost_1_86_0
)


# FetchContent_Declare(
#   nlohmann_json
#   GIT_REPOSITORY https://github.com/nlohmann/json.git
#   GIT_TAG v3.12.0
# )

# FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(
  TradingSystem PRIVATE
    ws2_32
    mswsock
    wsock32
)
