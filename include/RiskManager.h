#pragma once
#include "Execution_engine.h"
#include "Portfolio.h"
#include "Bar.h"
#include "OrderType.h"


class RiskManager {
public:
    RiskManager(double maxDrawdownPct = 0.05, double maxPositionPct = 0.10)
        : maxDrawdownPct(maxDrawdownPct), maxPositionPct(maxPositionPct) {}

    // Main risk check
    bool isOrderAllowed(OrderType signal, double price, const Portfolio& portfolio);

private:
    double maxDrawdownPct;   // e.g., 0.05 for 5% stop-loss
    double maxPositionPct;   // e.g., 0.10 for max 10% of equity per trade
};
