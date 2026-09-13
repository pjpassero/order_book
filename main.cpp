#include <iostream>
#include "OrderBook.h"


int main() {
    OrderBook Exchange;
    /*
    Exchange.add_ask(50, 100);
    Exchange.add_ask(75, 200);
    Exchange.add_ask(140, 350);
    Exchange.add_ask(25, 200);
    Exchange.add_ask(35, 400);
    Exchange.add_ask(35, 500);
    Exchange.add_bid(15, 100);
    Exchange.add_bid(17, 250);
    Exchange.add_bid(20, 100);
    Exchange.add_bid(25, 350);
    Exchange.add_bid(25, 500);
    Exchange.add_ask(15, 150);
    */
    
     
    
    Exchange.add_ask(25, 800);
    Exchange.add_bid(15, 450);
    Exchange.add_bid(26, 150);
    Exchange.add_ask(27, 500);
    
    Exchange.printBook();
    //Exchange.updatePriceLevels();
    return 0;
}
