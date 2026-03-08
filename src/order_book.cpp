#include "order_book.hpp"

namespace ob {

OrderBook::OrderBook() {}
OrderBook::~OrderBook() {}

std::vector<Trade> OrderBook::addOrder(const Order& ord) {
    std::vector<Trade> trades;
    // create shared ptr for the order so we can store if unfilled
    auto orderPtr = std::make_shared<Order>(ord);
    allOrders[ord.id] = orderPtr;
    
    if (ord.side == Side::Buy) {
        // match against asks
        while (orderPtr->quantity > 0 && !asks.empty()) {
            auto it = asks.begin();
            double bestAsk = it->first;
            if (bestAsk > orderPtr->price) break; // no match
            auto &listAtPrice = it->second;
            while (!listAtPrice.empty() && orderPtr->quantity > 0) {
                auto resting = listAtPrice.front();
                int tradedQty = std::min(orderPtr->quantity, resting->quantity);
                trades.push_back({orderPtr->id, resting->id, bestAsk, tradedQty});
                orderPtr->quantity -= tradedQty;
                resting->quantity -= tradedQty;
                if (resting->quantity == 0) {
                    allOrders.erase(resting->id);
                    listAtPrice.pop_front();
                }
            }
            if (listAtPrice.empty()) {
                asks.erase(it);
            }
        }
        if (orderPtr->quantity > 0) {
            bids[orderPtr->price].push_back(orderPtr);
        } else {
            allOrders.erase(orderPtr->id);
        }
    } else {
        // Sell side
        while (orderPtr->quantity > 0 && !bids.empty()) {
            auto it = bids.begin();
            double bestBid = it->first;
            if (bestBid < orderPtr->price) break;
            auto &listAtPrice = it->second;
            while (!listAtPrice.empty() && orderPtr->quantity > 0) {
                auto resting = listAtPrice.front();
                int tradedQty = std::min(orderPtr->quantity, resting->quantity);
                trades.push_back({resting->id, orderPtr->id, bestBid, tradedQty});
                orderPtr->quantity -= tradedQty;
                resting->quantity -= tradedQty;
                if (resting->quantity == 0) {
                    allOrders.erase(resting->id);
                    listAtPrice.pop_front();
                }
            }
            if (listAtPrice.empty()) {
                bids.erase(it);
            }
        }
        if (orderPtr->quantity > 0) {
            asks[orderPtr->price].push_back(orderPtr);
        } else {
            allOrders.erase(orderPtr->id);
        }
    }

    return trades;
}

bool OrderBook::cancelOrder(int orderId) {
    auto it = allOrders.find(orderId);
    if (it == allOrders.end()) return false;
    auto orderPtr = it->second;
    if (orderPtr->side == Side::Buy) {
        auto pit = bids.find(orderPtr->price);
        if (pit != bids.end()) {
            auto &lst = pit->second;
            lst.remove_if([orderId](const OrderPtr &o){ return o->id == orderId; });
            if (lst.empty()) bids.erase(pit);
        }
    } else {
        auto pit = asks.find(orderPtr->price);
        if (pit != asks.end()) {
            auto &lst = pit->second;
            lst.remove_if([orderId](const OrderPtr &o){ return o->id == orderId; });
            if (lst.empty()) asks.erase(pit);
        }
    }
    allOrders.erase(it);
    return true;
}

void OrderBook::print() const {
    std::cout << "Order book:\n";
    std::cout << "Bids:\n";
    for (const auto &p : bids) {
        std::cout << "  price=" << p.first << " qty=";
        int total = 0;
        for (auto &o : p.second) total += o->quantity;
        std::cout << total << "\n";
    }
    std::cout << "Asks:\n";
    for (const auto &p : asks) {
        std::cout << "  price=" << p.first << " qty=";
        int total = 0;
        for (auto &o : p.second) total += o->quantity;
        std::cout << total << "\n";
    }
}

} // namespace ob
