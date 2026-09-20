#pragma once
#include <string>
#include <vector>
#include "OrderBook.h"

struct Position {
 
    int position_size;
    double position_cost_average;
    Order initalOrder;
    bool pending;
    bool filled;
    
    Position(Order InitalOrder, double PositionCostAverage) : initalOrder(InitalOrder)
    {
        position_size = InitalOrder.quantity;
        position_cost_average = PositionCostAverage;
        pending = true;
        filled = false;
    }
    
    
};



class Participant {
    
private:
    std::string name;
    inline static int user_identifier = 1;
    double funds;
    std::vector<Position> holdings;
    
public:
    Participant(std::string Name, double Funds);
    ~Participant();
    
    int getID() {
        return user_identifier;
    }
    

    
};
