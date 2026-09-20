#pragma once
#include "Participant.h"
#include <vector>
#include "Exchange.h"

class Simulation {
    
private:
    Exchange& exchange;

public:
    Simulation(Exchange& exchange):exchange(exchange) {
        
    };
    void run(int orderCount);
    
};
