#pragma once
#include <vector>
#include <string>
#include "Bar.h"

class MarketData {
public:
    MarketData(const std::string& filename);
    bool hasNext() const;
    Bar getNextBar();

private:
    std::vector<Bar> bars;
    size_t currentIndex = 0;
};
