#include "Simulation.h"



void Simulation::run(int orderCount) {
    
    for(int  i = 0; i < orderCount; i++) {
        Participant& random_participant = exchange.get_random_participant();
        int price = 40 + (rand() % 11);
        int quantity = 100 + (rand() % 901);
        Side side;
        
        if(rand() % 2 == 0) {
            side = Bid;
        }else {
            side = Ask;
        }
        
        Order new_order(price, quantity, side);
        exchange.place_trade(random_participant, new_order);
    }
    
}
