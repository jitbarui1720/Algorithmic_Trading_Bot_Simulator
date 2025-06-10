#include "RSIStrategy.h"

RSIStrategy::RSIStrategy(int period) : period(period) {}

double RSIStrategy::computeRSI(const std::vector<Candle>& candles, int idx) {
    if (idx < period) return 50.0;

    double gain = 0, loss = 0;
    for (int i = idx - period + 1; i <= idx; ++i) {
        double diff = candles[i].close - candles[i - 1].close;
        if (diff > 0) gain += diff;
        else loss -= diff;
    }

    if (loss == 0) return 100.0;
    double rs = gain / loss;
    return 100.0 - (100.0 / (1.0 + rs));
}
