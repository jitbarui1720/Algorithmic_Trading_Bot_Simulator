#pragma once
class Portfolio {
private:
    double cash;
    int holdings;

public:
    Portfolio(double initialCash = 10000.0);

    double getCash() const;
    int getHoldings() const;
    double getEquity(double currentPrice) const;

    void increaseCash(double amount);
    void decreaseCash(double amount);
    void increaseHoldings(int units);
    void decreaseHoldings(int units);
};
