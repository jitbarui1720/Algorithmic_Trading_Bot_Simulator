#include "RiskManager.h"
#include <iostream>

RiskManager::RiskManager(double maxDrawdownPct, double maxPositionPct)
    : maxDrawdownPct(maxDrawdownPct), maxPositionPct(maxPositionPct) {}

bool RiskManager::isOrderAllowed(OrderType signal, double price, const Portfolio& portfolio) {
    if (price <= 0.0) {
        std::cerr << "RiskManager: Invalid price\n";
        return false;
    }

    // SELL signal risk check — stop-loss logic
    if (signal == OrderType::SELL && portfolio.isHolding()) {
        double entryPrice = portfolio.getEntryPrice();
        if (entryPrice <= 0.0) {
            std::cerr << "RiskManager: Invalid entry price\n";
            return false;
        }

        double unrealizedLoss = entryPrice - price;
        double drawdownPct = unrealizedLoss / entryPrice;

        if (drawdownPct > maxDrawdownPct) {
            std::cerr << "RiskManager: Stop-loss triggered. Drawdown = "
                      << (drawdownPct * 100.0) << "% > Max allowed = "
                      << (maxDrawdownPct * 100.0) << "%\n";
            return false;
        }
    }

    // BUY signal risk check — position size logic
    if (signal == OrderType::BUY) {
        double maxAllowed = portfolio.getEquity() * maxPositionPct;
        if (price > maxAllowed) {
            std::cerr << "RiskManager: Buy order price exceeds max position size ("
                      << (maxPositionPct * 100.0) << "% of equity)\n";
            return false;
        }
    }

    return true;
}
