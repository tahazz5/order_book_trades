#include "order_book.hpp"
#include <iostream>

int main() {
    ob::OrderBook book;
    
    // example sequence
    std::cout << "Adding orders...\n";
    auto trades1 = book.addOrder({1, ob::Side::Buy, 100.0, 10});
    auto trades2 = book.addOrder({2, ob::Side::Sell, 101.0, 5});
    auto trades3 = book.addOrder({3, ob::Side::Sell, 99.0, 7});

    for (const auto &t : trades3) {
        std::cout << "Trade executed: buy=" << t.buyOrderId
                  << " sell=" << t.sellOrderId
                  << " price=" << t.price
                  << " qty=" << t.quantity << "\n";
    }

    book.print();

    std::cout << "Cancelling order 1\n";
    book.cancelOrder(1);
    book.print();

    return 0;
}
