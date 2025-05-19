#include "RSIStrategy.h"

OrderType RSIStrategy::generateSignal(const std::vector<Bar>& history) {
    if (history.size() < 15) return OrderType::HOLD;

    double gain = 0, loss = 0;
    for (size_t i = history.size() - 14; i < history.size(); ++i) {
        double diff = history[i].close - history[i - 1].close;
        if (diff > 0) gain += diff;
        else loss -= diff;
    }

    if (loss == 0) return OrderType::BUY;
    double rs = gain / loss;
    double rsi = 100 - (100 / (1 + rs));

    if (rsi < 30) return OrderType::BUY;
    if (rsi > 70) return OrderType::SELL;
    return OrderType::HOLD;
}
