#include <string>
#include <vector>
#include <unordered_map>

enum Side {
    Bid,
    Ask
};


struct Order {
    int price;
    int quantity;
    Side side;
    int order_id;
    inline static int order_counter = 1;
    Order(int Price, int Quantity, Side Side) {
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
    std::unordered_map<int, int> bidLevels;
    std::unordered_map<int, int> askLevels;

public:
    OrderBook();
    ~OrderBook();
    void add_bid(int Price, int Quantity);
    void add_ask(int Price, int Quantity);
    void add_bid(Order order);
    void add_ask(Order order);
    void printAsks();
    void printBook();
    void updatePriceLevels();
    void process_order(Order order);
    std::string getDepth();
    
};
