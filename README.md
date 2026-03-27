# order_book_trades

A minimal **C++ order book trading** example. This project implements a simple limit order book that supports adding, matching, and cancelling orders for a basic trading simulation.

## What is an Order Book?

An order book is a data structure used in financial markets to record buy and sell orders for a particular asset. It maintains two sides:
- **Bids**: Buy orders, sorted by price in descending order (highest price first)
- **Asks**: Sell orders, sorted by price in ascending order (lowest price first)

When a new order is added, the system attempts to match it against existing orders on the opposite side. If the prices cross (e.g., a buy order at $100 matches a sell order at $99), a trade is executed.

## Features

- **Limit Orders**: Orders with a specified price and quantity
- **Order Matching**: Automatic matching of buy and sell orders based on price-time priority
- **Order Cancellation**: Ability to cancel pending orders
- **Trade Reporting**: Returns details of executed trades

## How It Works

1. **Adding an Order**:
   - For a buy order, it tries to match against the lowest ask price
   - For a sell order, it tries to match against the highest bid price
   - If no match, the order is added to the book
   - If partial match, the remaining quantity stays in the book

2. **Matching Algorithm**:
   - Uses price-time priority: best price first, then FIFO within the same price level
   - Executes trades until no more matches possible

3. **Data Structures**:
   - `std::map<double, std::list<OrderPtr>>` for price levels (ordered by price)
   - `std::map<int, OrderPtr>` for quick order lookup by ID

## Building

This project uses CMake. To build:

```sh
mkdir build && cd build
cmake ..
cmake --build .
```

## Running

After building, run the executable:

```sh
./order_book_trades
```

You will see a small demonstration of order matching and book state.

## Running Tests

Build and run the test executable:

```sh
cd build
./test_order_book
```

## Layout

* `include/order_book.hpp` – Order book API and data structures
* `src/order_book.cpp` – Implementation of the matching engine
* `src/main.cpp` – Simple driver showing usage
* `tests/test_order_book.cpp` – Unit tests

## Performance Considerations

This implementation uses standard C++ containers (`std::map`, `std::list`) which provide logarithmic time complexity for insertions and lookups. For high-frequency trading systems, more optimized data structures (like skip lists or custom allocators) would be needed.

Feel free to extend or integrate into your own trading/simulation system.
