#pragma once

#include <map>
#include <list>
#include <memory>
#include <iostream>
#include <vector>

namespace ob {

enum class Side { Buy, Sell };

struct Order {
    int id;
    Side side;
    double price;
    int quantity;
};

struct Trade {
    int buyOrderId;
    int sellOrderId;
    double price;
    int quantity;
};

class OrderBook {
public:
    OrderBook();
    ~OrderBook();

    // add a new limit order. If it matches, trades are generated.
    std::vector<Trade> addOrder(const Order& ord);
    bool cancelOrder(int orderId);
    void print() const;

private:
    using OrderPtr = std::shared_ptr<Order>;
    // price -> list of orders at that price
    std::map<double, std::list<OrderPtr>, std::greater<>> bids; // descending
    std::map<double, std::list<OrderPtr>> asks; // ascending
    std::map<int, OrderPtr> allOrders;
};

} // namespace ob
