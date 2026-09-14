#include <string>
#include <vector>
#include <unordered_map>

enum Side {
    Bid,
    Ask,
    Buy,
    Sell
};

enum OrderType {
    Limit,
    Market
};


struct Order {
    int price;
    int quantity;
    Side side;
    OrderType type;
    int order_id;
    inline static int order_counter = 1;
    Order(int Quantity, Side Side, OrderType Type) {
        price = 0.0;
        quantity = Quantity;
        side = Side;
        order_id = order_counter++;
        type = Type;
    }
    Order(int Price, int Quantity, Side Side) {
        price = Price;
        quantity = Quantity;
        side = Side;
        order_id = order_counter++;
        type= Limit;
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
    void add_order(Order order);
    std::string getDepth();
    
};
