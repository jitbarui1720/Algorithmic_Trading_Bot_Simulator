#pragma once
#include "MarketData.h"
#include "RSIStrategy.h"
#include "Portfolio.h"
#include "Execution_engine.h"
#include "RiskManager.h"


class Simulator {
public:
    void run(MarketData& market, RSIStrategy& strategy, Portfolio& portfolio, Execution_engine& executor);
};
