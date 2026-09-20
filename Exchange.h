#pragma once
#include "Participant.h"
#include <vector>
#include <algorithm>
#include "OrderBook.h"

class Exchange {
    
private:
    
    OrderBook orderbook;
    std::vector<Participant> traders;
    
public:
    Exchange();
    ~Exchange();
    void register_trader(Participant &trader);
    void place_trade(Participant &trader, Order &order);
    void cancel_trade(int TradeNumber);
    void printBook();
    void printPriceLevelDepth();
    
    Participant& get_random_participant();
    
};
