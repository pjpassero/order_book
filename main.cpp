#include <iostream>
#include "OrderBook.h"


int main() {
    OrderBook Exchange;
    
    Exchange.add_ask(50, 100);
    Exchange.add_ask(75, 200);
    Exchange.add_ask(140, 350);
    Exchange.add_ask(25, 200);
    Exchange.add_ask(25, 400);
    Exchange.add_ask(25, 500);


    Exchange.printAsks();
    

    return 0;
}
