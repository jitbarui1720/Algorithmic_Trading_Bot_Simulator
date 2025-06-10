#ifndef BAR_H
#define BAR_H

#include <string>

struct Candle {
    std::string timestamp;
    double open, high, low, close, volume;
};

#endif
