#include <string>
#include <vector>
#include <unordered_map>

struct Order {
    int price;
    int quantity;
    std::string side;
    int order_id;
    inline static int order_counter = 1;
    Order(int Price, int Quantity, std::string Side) {
        price = Price;
        quantity = Quantity;
        side = Side;
        order_id = order_counter++;
    }
};




class OrderBook {
    
private:
    std::vector<Order> bids;
    std::vector<Order> asks;
    
public:
    OrderBook();
    ~OrderBook();
    void add_bid(int Price, int Quantity);
    void add_ask(int Price, int Quantity);
    void printAsks();
    std::string getDepth();
    
};
