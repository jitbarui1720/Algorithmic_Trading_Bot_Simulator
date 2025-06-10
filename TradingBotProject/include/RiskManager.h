#ifndef RISKMANAGER_H
#define RISKMANAGER_H

class RiskManager {
private:
    double maxDrawdownPct;
    double maxPositionPct;

public:
    RiskManager(double maxDrawdownPct = 0.05, double maxPositionPct = 0.10);
    bool shouldStopLoss(double entryPrice, double currentPrice) const;
};

#endif
