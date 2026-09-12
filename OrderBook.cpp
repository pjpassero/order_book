#include "OrderBook.h"
#include <iostream>
#include <iterator>
#include <iomanip>
OrderBook::OrderBook() {
    
}
OrderBook::~OrderBook() {
    
}

void OrderBook::add_ask(int Price, int Quantity) {
    Order new_ask = Order(Price, Quantity, "ask");
    for(auto it = asks.begin(); it!= asks.end(); ++it) {
        if(new_ask.price < it->price) {
            asks.insert(it, new_ask);
            return;
        }
    }
    asks.push_back(new_ask);

}


void OrderBook::add_bid(int Price, int Quantity) {
    Order new_bid = Order(Price, Quantity, "bid");
    for(auto it = bids.begin(); it!= bids.end(); ++it) {
        if(new_bid.price < it->price) {
            bids.insert(it, new_bid);
            return;
        }
    }
    bids.push_back(new_bid);
}


void OrderBook::printAsks() {
    std::cout << "\n=================== ASK BOOK ===================\n";
    std::cout << std::left
              << std::setw(12) << "PRICE"
              << std::setw(12) << "QUANTITY"
              << "ORDER NUMBER" << "\n";
    std::cout << "------------------------------------------------\n";

    for (auto it = asks.begin(); it != asks.end(); ++it) {
        std::string price_str = "$" + std::to_string(it->price);
        
        std::cout << std::left
                  << std::setw(12) << price_str
                  << std::setw(12) << it->quantity
                  << "#" << it->order_id << "\n";
    }
    std::cout << "================================================\n\n";
}
