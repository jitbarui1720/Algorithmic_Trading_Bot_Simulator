#ifndef RSISTRATEGY_H
#define RSISTRATEGY_H

#include "Bar.h"
#include <vector>

class RSIStrategy {
    int period;

public:
    RSIStrategy(int period = 14);
    double computeRSI(const std::vector<Candle>& candles, int idx);
};

#endif
