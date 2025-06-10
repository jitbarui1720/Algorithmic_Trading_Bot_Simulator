#include "RiskManager.h"

RiskManager::RiskManager(double maxDrawdownPct, double maxPositionPct)
    : maxDrawdownPct(maxDrawdownPct), maxPositionPct(maxPositionPct) {}

bool RiskManager::shouldStopLoss(double entryPrice, double currentPrice) const {
    return currentPrice < entryPrice * (1.0 - maxDrawdownPct);
}
