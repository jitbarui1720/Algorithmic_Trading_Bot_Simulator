#include "Portfolio.h"

Portfolio::Portfolio() : cash(10000.0), holdings(0.0), entryPrice(0.0) {}

void Portfolio::buy(double price) {
    if (cash > 0) {
        holdings = cash / price;
        entryPrice = price;
        cash = 0;
    }
}

void Portfolio::sell(double price) {
    if (holdings > 0) {
        cash = holdings * price;
        holdings = 0;
    }
}

double Portfolio::getHoldings() const {
    return holdings;
}

double Portfolio::getEntryPrice() const {
    return entryPrice;
}

double Portfolio::getEquity(double currentPrice) const {
    return cash + (holdings * currentPrice);
}
