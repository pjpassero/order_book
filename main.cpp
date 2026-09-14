#include <iostream>
#include "OrderBook.h"


int main() {
    OrderBook Exchange;
  
    Order myMarketOrder(100, Buy, Market);
    Order myMarketOrderSell(30, Sell, Market);
    Order myBid(25,100,Bid);
    
    //Exchange.add_bid(myBid);
    Exchange.add_ask(57, 25);
    Exchange.add_ask(60, 45);
    Exchange.add_bid(25, 100);
    Exchange.add_bid(40, 250);
    Exchange.add_order(myMarketOrderSell);
    Exchange.add_order(myMarketOrder);

    /*
    Exchange.add_ask(25, 800);
    Exchange.add_bid(15, 450);
    Exchange.add_bid(26, 150);
    Exchange.add_ask(27, 500);
    */
    Exchange.printBook();
    //Exchange.updatePriceLevels();
    return 0;
}
