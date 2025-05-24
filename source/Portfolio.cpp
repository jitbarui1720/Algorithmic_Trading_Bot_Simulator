#include "Portfolio.h"

Portfolio::Portfolio(double initialCash) : cash(initialCash), holdings(0) {}

double Portfolio::getCash() const {
    return cash;
}

int Portfolio::getHoldings() const {
    return holdings;
}

double Portfolio::getEquity(double currentPrice) const {
    return cash + (holdings * currentPrice);
}

void Portfolio::increaseCash(double amount) {
    cash += amount;
}

void Portfolio::decreaseCash(double amount) {
    if (amount <= cash) {
        cash -= amount;
    }
}

void Portfolio::increaseHoldings(int units) {
    holdings += units;
}

void Portfolio::decreaseHoldings(int units) {
    if (units <= holdings) {
        holdings -= units;
    }
}
