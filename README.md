# order_book_trades

A minimal **C++ order book trading** example.  It implements a simple limit order book that supports adding, matching, and cancelling orders.

## Building

This project uses CMake.  To build:

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

You will see a small demonstration of matching and book state.

## Layout

* `include/order_book.hpp` – order book API and data structures
* `src/order_book.cpp` – implementation of the matching engine
* `src/main.cpp` – simple driver showing usage

Feel free to extend or integrate into your own trading/simulation system.
