#include "Simulator.h"
#include "OrderType.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

void Simulator::run(MarketData& market, RSIStrategy& strategy, Portfolio& portfolio, Execution_engine& executor) {
    std::vector<Bar> history;
    std::vector<double> equityCurve;
    std::vector<double> returns;
    int totalTrades = 0;
    int wins = 0;

    double initialBalance = 100000.0;
    portfolio.setEquity(initialBalance);

    while (market.hasNext()) {
        Bar bar = market.getNextBar();
        history.push_back(bar);

        OrderType signal = strategy.generateSignal(history);
        executor.executeOrder(signal, bar.close, portfolio);

        if (signal != OrderType::HOLD) {
            ++totalTrades;
            if (signal == OrderType::BUY && portfolio.getEquity() > initialBalance) {
                ++wins;
            }
        }

        equityCurve.push_back(portfolio.getEquity());
    }

    for (size_t i = 1; i < equityCurve.size(); ++i) {
        double ret = (equityCurve[i] / equityCurve[i - 1]) - 1.0;
        returns.push_back(ret);
    }

    double avgReturn = 0, stdDev = 0;
    for (double r : returns) avgReturn += r;
    avgReturn /= returns.size();
    for (double r : returns) stdDev += (r - avgReturn) * (r - avgReturn);
    stdDev = std::sqrt(stdDev / returns.size());

    double sharpe = stdDev != 0 ? avgReturn / stdDev * std::sqrt(252) : 0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Initial Balance: $" << initialBalance << "\n";
    std::cout << "Final Equity: $" << portfolio.getEquity() << "\n";
    std::cout << "Total Trades: " << totalTrades << "\n";
    std::cout << "Win Rate: " << (totalTrades ? (wins * 100.0 / totalTrades) : 0) << "%\n";
    std::cout << "Sharpe Ratio: " << sharpe << "\n";
}
