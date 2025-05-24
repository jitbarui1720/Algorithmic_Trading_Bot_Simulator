#include "Execution_engine.h"

#include "Execution_engine.h"
#include <iostream>

void Execution_engine::executeOrder(OrderType signal, double price, Portfolio& portfolio) {
    if (signal == OrderType::BUY) {
        if (portfolio.getCash() >= price) {
            portfolio.decreaseCash(price);
            portfolio.increaseHoldings(1);
            std::cout << "Bought 1 unit at $" << price << std::endl;
        } else {
            std::cout << "Buy failed: Not enough cash.\n";
        }
    } 
    else if (signal == OrderType::SELL) {
        if (portfolio.getHoldings() > 0) {
            portfolio.increaseCash(price);
            portfolio.decreaseHoldings(1);
            std::cout << "Sold 1 unit at $" << price << std::endl;
        } else {
            std::cout << "Sell failed: No holdings.\n";
        }
    }
}
