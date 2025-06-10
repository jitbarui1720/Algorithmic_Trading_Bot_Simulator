#include "MarketData.h"
#include "RSIStrategy.h"
#include "Portfolio.h"
#include "RiskManager.h"
#include <iostream>
#include <vector>
#include <cmath>

struct Trade {
    std::string timestamp;
    double price;
    std::string type; // "BUY" or "SELL"
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: trading_bot <csv_file_path>\n";
        return 1;
    }

    std::string csvFile = argv[1];
    auto candles = MarketData::loadCSV(csvFile);

    if (candles.empty()) {
        std::cerr << "No candle data loaded.\n";
        return 1;
    }

    Portfolio portfolio;
    RiskManager riskManager(0.01);  // ✅ 1% stop-loss
    RSIStrategy strategy;
    std::vector<Trade> trades;
    std::vector<double> equityHistory;

    for (size_t i = 1; i < candles.size(); ++i) {
        double rsi = strategy.computeRSI(candles, i);
        double price = candles[i].close;
        equityHistory.push_back(portfolio.getEquity(price));

        if (portfolio.getHoldings() == 0 && rsi < 30.0) {
            portfolio.buy(price);
            trades.push_back({candles[i].timestamp, price, "BUY"});
            std::cout << candles[i].timestamp << " BUY at " << price << "\n";
        } else if (portfolio.getHoldings() > 0 && (rsi > 70.0 || riskManager.shouldStopLoss(portfolio.getEntryPrice(), price))) {
            portfolio.sell(price);
            trades.push_back({candles[i].timestamp, price, "SELL"});
            std::cout << candles[i].timestamp << " SELL at " << price << "\n";
        }
    }

    double finalPrice = candles.back().close;
    double finalEquity = portfolio.getEquity(finalPrice);

    std::vector<double> returns;
    for (size_t i = 1; i < equityHistory.size(); ++i) {
        double r = (equityHistory[i] - equityHistory[i - 1]) / equityHistory[i - 1];
        returns.push_back(r);
    }

    double avgReturn = 0, sumSq = 0;
    for (double r : returns) {
        avgReturn += r;
        sumSq += r * r;
    }
    avgReturn /= returns.size();
    double stdDev = std::sqrt(sumSq / returns.size() - avgReturn * avgReturn);
    double sharpe = (stdDev == 0) ? 0 : (avgReturn / stdDev) * std::sqrt(returns.size());

    double bestBuyPrice = 1e9, bestSellPrice = 0;
    std::string bestBuyTime, bestSellTime;
    int tradeCount = 0;

    for (const auto& t : trades) {
        if (t.type == "BUY" && t.price < bestBuyPrice) {
            bestBuyPrice = t.price;
            bestBuyTime = t.timestamp;
        } else if (t.type == "SELL" && t.price > bestSellPrice) {
            bestSellPrice = t.price;
            bestSellTime = t.timestamp;
        }
        tradeCount++;
    }

    std::cout << "\nFinal Equity: $" << finalEquity << "\n";
    std::cout << "Number of trades: " << tradeCount << "\n";
    std::cout << "Best Buy: " << bestBuyTime << " at $" << bestBuyPrice << "\n";
    std::cout << "Best Sell: " << bestSellTime << " at $" << bestSellPrice << "\n";
    std::cout << "Sharpe Ratio: " << sharpe << "\n";

    // === Maximum Theoretical Profit Calculation ===
    double minPrice = candles[0].close;
    double maxProfit = 0.0;
    std::string minTime = candles[0].timestamp;
    std::string maxTime = candles[0].timestamp;

    for (size_t i = 1; i < candles.size(); ++i) {
        double potentialProfit = candles[i].close - minPrice;
        if (potentialProfit > maxProfit) {
            maxProfit = potentialProfit;
            maxTime = candles[i].timestamp;
        }
        if (candles[i].close < minPrice) {
            minPrice = candles[i].close;
            minTime = candles[i].timestamp;
        }
    }

    std::cout << "\nMaximum Theoretical Profit (1 Trade):\n";
    std::cout << "Buy at: " << minTime << " ($" << minPrice << ")\n";
    std::cout << "Sell at: " << maxTime << " ($" << (minPrice + maxProfit) << ")\n";
    std::cout << "Max Profit: $" << maxProfit << "\n";

    return 0;
}
