#include <iostream>
#include "Participant.h"
#include "Exchange.h"
#include "Simulation.h"

int main() {
    
    Exchange exchange;
    Simulation simulation_one(exchange);

    //Regular "People" of sorts
    Participant Thomas("Tom", 10000);
    Participant Robert("Bob", 25000);
    Participant James("James", 50000);

    
    //Market Makers
    Participant marketMakerA("MarketMakerA", 100000);
    
    
    
    Order myMarketOrder(100, Buy, Market);
    Order myBid(45, 250, Bid);
    Order myAsk(47,500, Ask);
    
    exchange.register_trader(Thomas);
    exchange.register_trader(Robert);
    exchange.register_trader(James);
    exchange.register_trader(marketMakerA);
    
    simulation_one.run(100);
   
    
    
    exchange.printBook();
    exchange.printPriceLevelDepth();
    return 0;
}
