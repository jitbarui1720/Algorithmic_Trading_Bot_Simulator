#pragma once
#include <vector>
#include "Bar.h"
#include "OrderType.h"

class RSIStrategy {
public:
    OrderType generateSignal(const std::vector<Bar>& history);
};
