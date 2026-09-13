#include "OrderBook.h"
#include <iostream>
#include <iterator>
#include <iomanip>
OrderBook::OrderBook() {
    
}
OrderBook::~OrderBook() {
    
}



void OrderBook::add_ask(int Price, int Quantity) {
    Order new_ask = Order(Price, Quantity, Ask);
    process_order(new_ask);
}

void OrderBook::add_ask(Order order) {
    for (auto it = asks.begin(); it != asks.end(); ++it) {
        if(order.price < it->price) {
            asks.insert(it, order);
            return;
        }
    }
    asks.push_back(order);

}


void OrderBook::add_bid(int Price, int Quantity) {
    Order new_bid = Order(Price, Quantity, Bid);
    process_order(new_bid);
}

void OrderBook::add_bid(Order order) {
    for (auto it = bids.begin(); it != bids.end(); ++it) {
        if(order.price > it->price) {
            bids.insert(it, order);
            return;
        }
    }
    bids.push_back(order);

}

void OrderBook::updatePriceLevels() {
    for(int i = 0; i < bids.size(); i++) {
        bidLevels[bids[i].price] += bids[i].quantity;
    }
    
    for(int i = 0; i < asks.size(); i++) {
        askLevels[asks[i].price] += asks[i].quantity;
    }
    
    /*
    for (auto const& [bid, quantity] : bidLevels) {
        std::cout << '\n' << "Bid Level: " << bid << " Quantity: " << quantity << "\n";
    }
    */
}


void OrderBook::process_order(Order order) {
    
    switch (order.side) {
        case Bid: {
            bool canMatch = true;
            
            while(canMatch) {
                if(asks.empty()) {
                    add_bid(order);
                    canMatch = false;
                } else if (order.price >= asks[0].price) {
                    int fillAmount = 0;
                    if(order.quantity > asks[0].quantity) {
                        fillAmount = asks[0].quantity;
                        order.quantity = order.quantity - fillAmount;
                        asks.erase(asks.begin());
                    } else if (order.quantity <= asks[0].quantity) {
                        fillAmount = order.quantity;
                        asks[0].quantity = asks[0].quantity - fillAmount;
                        order.quantity = order.quantity - fillAmount;
                        if(asks[0].quantity == 0) {
                            asks.erase(asks.begin());
                            canMatch = false;
                        }
                        canMatch = false;
                    }
                } else {
                    canMatch = false;
                    add_bid(order);
                }
            }
            break;
        }
        case Ask: {
            bool canMatch = true;
            while(canMatch) {
                if(bids.empty()) {
                    add_ask(order);
                    canMatch = false;
                } else if (order.price <= bids[0].price) {
                    int fillAmount = 0;
                    if(order.quantity > bids[0].quantity) {
                        fillAmount = bids[0].quantity;
                        order.quantity = order.quantity - fillAmount;
                        bids.erase(bids.begin());
                    } else if(order.quantity <= bids[0].quantity) {
                        fillAmount = order.quantity;
                        bids[0].quantity = bids[0].quantity - fillAmount;
                        order.quantity = order.quantity - fillAmount;
                        if(bids[0].quantity == 0) {
                            bids.erase(bids.begin());
                        }
                        canMatch = false;
                    }
                } else {
                    canMatch = false;
                    add_ask(order);
                }
            }
            break;
        }
                
    }
    
}




void OrderBook::printBook() {
    std::cout << "\n ===================== ORDER BOOK NEW =====================\n\n";
    std::cout << std::left << std::setw(28) << "BIDS" << "ASKS\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout<< std::left << std::setw(14) << "PRICE" <<
    std::setw(14) << "Quantity" << std::setw(14) << "PRICE" <<
    std::setw(14) << "Quantity";
    std::cout << '\n';
    size_t maxRows = std::max(asks.size(), bids.size());
    
    for(int i = 0; i < maxRows; i++) {
      
        if(i < bids.size()) {
            std::cout<< std::left << std::setw(14) << bids[i].price <<
            std::setw(14) << bids[i].quantity;
        } else {
            std::cout<< std::left << std::setw(14) << "" <<
            std::setw(14) << "";
        }
        if(i < asks.size()) {
            std::cout<< std::left << std::setw(14) << asks[i].price <<
            std::setw(14) << asks[i].quantity;
        } else {
            std::cout<< std::left << std::setw(14) << "" <<
            std::setw(14) << "";
        }
        
       
        std::cout << '\n';
    }
    std::cout << '\n';
}
    
