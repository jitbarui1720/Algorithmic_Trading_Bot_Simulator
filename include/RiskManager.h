#pragma once
#include "Execution_engine.h"
#include "Portfolio.h"
#include "Bar.h"

class RiskManager {
    double maxDrawdownPct = 0.2; // 20% stop-loss

public:
    bool isOrderAllowed(OrderType signal, double price, const Portfolio& portfolio);
};
