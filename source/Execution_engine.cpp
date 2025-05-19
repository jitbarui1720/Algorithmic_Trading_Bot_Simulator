#include "Execution_engine.h"

void Execution_engine::executeOrder(OrderType signal, double price, Portfolio& portfolio) {
    if (signal == OrderType::BUY) {
        portfolio.setEquity(portfolio.getEquity() * 1.01); // Simulated return
    } else if (signal == OrderType::SELL) {
        portfolio.setEquity(portfolio.getEquity() * 0.99); // Simulated loss
    }
}
