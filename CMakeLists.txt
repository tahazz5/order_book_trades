cmake_minimum_required(VERSION 3.10)
project(order_book_trades LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(order_book_trades
    src/main.cpp
    src/order_book.cpp
)

# simple test executable
add_executable(test_order_book
    tests/test_order_book.cpp
    src/order_book.cpp
)
