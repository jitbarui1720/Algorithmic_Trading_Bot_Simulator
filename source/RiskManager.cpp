#include "RiskManager.h"

bool RiskManager::isOrderAllowed(OrderType signal, double price, const Portfolio& portfolio) {
    if (signal == OrderType::SELL && portfolio.isHolding()) {
        double unrealizedLoss = portfolio.getEntryPrice() - price;
        if (unrealizedLoss / portfolio.getEntryPrice() > maxDrawdownPct) {
            return false; // Stop-loss hit
        }
    }
    return true;
}
