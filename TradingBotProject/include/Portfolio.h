#ifndef PORTFOLIO_H
#define PORTFOLIO_H

class Portfolio {
private:
    double cash;
    double holdings;
    double entryPrice;

public:
    Portfolio();
    void buy(double price);
    void sell(double price);
    double getHoldings() const;
    double getEntryPrice() const;
    double getEquity(double currentPrice) const;
};

#endif
