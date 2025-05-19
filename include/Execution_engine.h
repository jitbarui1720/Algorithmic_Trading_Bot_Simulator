#pragma once
#include "OrderType.h"
#include "Bar.h"
#include "Portfolio.h"

class Execution_engine {
public:
    void executeOrder(OrderType signal, double price, Portfolio& portfolio);
};
