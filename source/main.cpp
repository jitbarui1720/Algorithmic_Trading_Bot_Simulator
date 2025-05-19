#include "MarketData.h"
#include "RSIStrategy.h"
#include "Portfolio.h"
#include "Execution_engine.h"
#include "Simulator.h"

int main() {
    MarketData market("Data/btc_usdt.csv");
    RSIStrategy strategy;
    Portfolio portfolio;
    Execution_engine executor;
    Simulator simulator;

    simulator.run(market, strategy, portfolio, executor);
    return 0;
}
