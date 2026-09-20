#include "OrderBook.h"
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>



OrderBook::OrderBook() {
    
}
OrderBook::~OrderBook() {
    
}

void OrderBook::add_order(Order order) {
    process_order(order);
}

void OrderBook::add_ask(int Price, int Quantity) {
    Order new_ask = Order(Price, Quantity, Ask);
    process_order(new_ask);
}

void OrderBook::add_ask(Order order) {
    for (auto it = asks.begin(); it != asks.end(); ++it) {
        if(order.price < it->price) {
            asks.insert(it, order);
            return;
        }
    }
    asks.push_back(order);

}


void OrderBook::add_bid(int Price, int Quantity) {
    Order new_bid = Order(Price, Quantity, Bid);
    process_order(new_bid);
}

void OrderBook::add_bid(Order order) {
    for (auto it = bids.begin(); it != bids.end(); ++it) {
        if(order.price > it->price) {
            bids.insert(it, order);
            return;
        }
    }
    bids.push_back(order);

}

void OrderBook::updatePriceLevels() {
    for(int i = 0; i < bids.size(); i++) {
        bidLevels[bids[i].price] += bids[i].quantity;
    }
    
    for(int i = 0; i < asks.size(); i++) {
        askLevels[asks[i].price] += asks[i].quantity;
    }
    
    /*
    for (auto const& [bid, quantity] : bidLevels) {
        std::cout << '\n' << "Bid Level: " << bid << " Quantity: " << quantity << "\n";
    }
    */
}


void OrderBook::push_order(Order &order) {
    add_order(order);
}


void OrderBook::process_order(Order order) {
    switch (order.type) {
        case Limit: {
            switch (order.side) {
                case Bid: {
                    while (
                        order.quantity > 0 &&
                        !asks.empty() &&
                        order.price >= asks[0].price
                    ) {
                        int fillAmount = std::min(
                            order.quantity,
                            asks[0].quantity
                        );

                        order.quantity -= fillAmount;
                        asks[0].quantity -= fillAmount;

                        if (asks[0].quantity == 0) {
                            asks.erase(asks.begin());
                        }
                    }

                    if (order.quantity > 0) {
                        add_bid(order);
                    }

                    break;
                }

                case Ask: {
                    while (
                        order.quantity > 0 &&
                        !bids.empty() &&
                        order.price <= bids[0].price
                    ) {
                        int fillAmount = std::min(
                            order.quantity,
                            bids[0].quantity
                        );

                        order.quantity -= fillAmount;
                        bids[0].quantity -= fillAmount;

                        if (bids[0].quantity == 0) {
                            bids.erase(bids.begin());
                        }
                    }

                    if (order.quantity > 0) {
                        add_ask(order);
                    }

                    break;
                }

                default: {
                    break;
                }
            }

            break;
        }

        case Market: {
            int originalQuantity = order.quantity;
            long long totalExecutionValue = 0;
            int totalQuantityFilled = 0;
            int bookOrdersConsumed = 0;

            switch (order.side) {
                case Buy: {
                    while (order.quantity > 0 && !asks.empty()) {
                        int fillAmount = std::min(
                            order.quantity,
                            asks[0].quantity
                        );

                        int fillPrice = asks[0].price;

                        totalExecutionValue +=
                            static_cast<long long>(fillAmount) * fillPrice;

                        totalQuantityFilled += fillAmount;
                        order.quantity -= fillAmount;
                        asks[0].quantity -= fillAmount;

                        bookOrdersConsumed++;

                        if (asks[0].quantity == 0) {
                            asks.erase(asks.begin());
                        }
                    }

                    break;
                }

                case Sell: {
                    while (order.quantity > 0 && !bids.empty()) {
                        int fillAmount = std::min(
                            order.quantity,
                            bids[0].quantity
                        );

                        int fillPrice = bids[0].price;

                        totalExecutionValue +=
                            static_cast<long long>(fillAmount) * fillPrice;

                        totalQuantityFilled += fillAmount;
                        order.quantity -= fillAmount;
                        bids[0].quantity -= fillAmount;

                        bookOrdersConsumed++;

                        if (bids[0].quantity == 0) {
                            bids.erase(bids.begin());
                        }
                    }

                    break;
                }

                default: {
                    break;
                }
            }

            std::cout << "\n--- MARKET ORDER RESULT ---\n";

            std::cout << "Requested Quantity: "
                      << originalQuantity << '\n';

            std::cout << "Quantity Filled: "
                      << totalQuantityFilled << '\n';

            std::cout << "Orders on Book Consumed: "
                      << bookOrdersConsumed << '\n';

            if (totalQuantityFilled > 0) {
                double averageFillPrice =
                    static_cast<double>(totalExecutionValue)
                    / totalQuantityFilled;

                std::cout << "Average Fill Price: "
                          << averageFillPrice << '\n';
            } else {
                std::cout << "Average Fill Price: N/A\n";
            }

            if (order.quantity > 0) {
                std::cout
                    << "No more liquidity in the market to fulfill this order!\n";

                std::cout << "Quantity Unfilled/Cancelled: "
                          << order.quantity << '\n';
            } else {
                std::cout << "Quantity Unfilled/Cancelled: 0\n";
            }

            std::cout << "---------------------------\n";

            break;
        }

        default: {
            break;
        }
    }
}



void OrderBook::printBook() {
    std::cout << "\n ===================== ORDER BOOK - ORDER DEPTH =====================\n\n";
    std::cout << std::left << std::setw(28) << "BIDS" << "ASKS\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout<< std::left << std::setw(14) << "PRICE" <<
    std::setw(14) << "Quantity" << std::setw(14) << "PRICE" <<
    std::setw(14) << "Quantity";
    std::cout << '\n';
    size_t maxRows = std::max(asks.size(), bids.size());
    
    for(int i = 0; i < maxRows; i++) {
      
        if(i < bids.size()) {
            std::cout<< std::left << std::setw(14) << bids[i].price <<
            std::setw(14) << bids[i].quantity;
        } else {
            std::cout<< std::left << std::setw(14) << "" <<
            std::setw(14) << "";
        }
        if(i < asks.size()) {
            std::cout<< std::left << std::setw(14) << asks[i].price <<
            std::setw(14) << asks[i].quantity;
        } else {
            std::cout<< std::left << std::setw(14) << "" <<
            std::setw(14) << "";
        }
        
       
        std::cout << '\n';
    }
    std::cout << '\n';
}


void OrderBook::printPriceLevelDepth() {

    std::cout << "\n ===================== ORDER BOOK - PRICE LEVEL DEPTH =====================\n\n";

    std::vector<std::pair<int, int>> bidDepth;
    std::vector<std::pair<int, int>> askDepth;

    if (!bids.empty()) {
        int currentPrice = bids[0].price;
        int totalQuantity = 0;

        for (int i = 0; i < bids.size(); i++) {
            if (bids[i].price == currentPrice) {
                totalQuantity += bids[i].quantity;
            } else {
                bidDepth.push_back({currentPrice, totalQuantity});

                currentPrice = bids[i].price;
                totalQuantity = bids[i].quantity;
            }
        }

        bidDepth.push_back({currentPrice, totalQuantity});
    }

    if (!asks.empty()) {
        int currentPrice = asks[0].price;
        int totalQuantity = 0;

        for (int i = 0; i < asks.size(); i++) {
            if (asks[i].price == currentPrice) {
                totalQuantity += asks[i].quantity;
            } else {
                askDepth.push_back({currentPrice, totalQuantity});

                currentPrice = asks[i].price;
                totalQuantity = asks[i].quantity;
            }
        }

        askDepth.push_back({currentPrice, totalQuantity});
    }

    std::cout << std::left << std::setw(28) << "BIDS" << "ASKS\n";
    std::cout << "--------------------------------------------------------\n";

    std::cout << std::left
              << std::setw(14) << "PRICE"
              << std::setw(14) << "Quantity"
              << std::setw(14) << "PRICE"
              << std::setw(14) << "Quantity"
              << '\n';

    size_t maxRows = std::max(bidDepth.size(), askDepth.size());

    for (size_t i = 0; i < maxRows; i++) {

        if (i < bidDepth.size()) {
            std::cout << std::left
                      << std::setw(14) << bidDepth[i].first
                      << std::setw(14) << bidDepth[i].second;
        } else {
            std::cout << std::left
                      << std::setw(14) << ""
                      << std::setw(14) << "";
        }

        if (i < askDepth.size()) {
            std::cout << std::left
                      << std::setw(14) << askDepth[i].first
                      << std::setw(14) << askDepth[i].second;
        } else {
            std::cout << std::left
                      << std::setw(14) << ""
                      << std::setw(14) << "";
        }

        std::cout << '\n';
    }

    std::cout << '\n';
}
