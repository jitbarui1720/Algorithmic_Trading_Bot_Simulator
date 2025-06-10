#ifndef MARKETDATA_H
#define MARKETDATA_H

#include "Bar.h"
#include <vector>
#include <string>

class MarketData {
public:
    static std::vector<Candle> loadCSV(const std::string& filename);
};

#endif
