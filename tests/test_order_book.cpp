#include "../include/order_book.hpp"
#include <cassert>
#include <iostream>

void run_tests() {
    ob::OrderBook book;
    auto t1 = book.addOrder({1, ob::Side::Buy, 50.0, 10});
    assert(t1.empty());
    auto t2 = book.addOrder({2, ob::Side::Sell, 49.0, 5});
    assert(t2.size() == 1);
    assert(t2[0].quantity == 5);
    auto t3 = book.addOrder({3, ob::Side::Sell, 50.0, 10});
    assert(t3.size() == 1);
    assert(t3[0].quantity == 5); // remaining
    book.cancelOrder(1);
    std::cout << "All tests passed\n";
}

int main(){
    run_tests();
    return 0;
}
