#include "Exchange.h"
#include <iostream>
#include <random>

Exchange::Exchange() {
    orderbook = OrderBook();
}

Exchange::~Exchange() {
    
}


void Exchange::register_trader(Participant& trader) {
    traders.push_back(trader);
    
}

void Exchange::place_trade(Participant &trader, Order &order) {
    for(int  i = 0; i < traders.size(); i++) {
        Participant &currentTrader = traders[i];
        if (currentTrader.getID() == trader.getID()) {
            orderbook.add_order(order);
            return;
        }
        
    }
    std::cout << "Trader Not found!" << std::endl;
}


void Exchange::printBook() {
    orderbook.printBook();
}
void Exchange::printPriceLevelDepth() {
    orderbook.printPriceLevelDepth();
}


Participant& Exchange::get_random_participant() {
    int index = rand() % traders.size();
    
    return traders[index];
}
