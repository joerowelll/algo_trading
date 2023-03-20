cmake_minimum_required(VERSION 3.10)

# set project name and language
project(PairsTradingStrategy CXX)

# set compiler flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# set include directories
include_directories(include)

# add source files
add_executable(pairs_trading_strategy src/pairs_trading_strategy.cpp src/ib_client.cpp)

# set link directories
link_directories(/path/to/ibapi/linux)

# link with Interactive Brokers API libraries
target_link_libraries(pairs_trading_strategy libibclient.so)