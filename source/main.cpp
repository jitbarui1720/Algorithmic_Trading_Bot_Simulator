#include "MarketData.h"
#include "RSIStrategy.h"
#include "Portfolio.h"
#include "Execution_engine.h"
#include "Simulator.h"

#include <iostream>
#include <filesystem>
#include <string>

int main(int argc, char* argv[]) {
    // Default values
    std::string dataFile = "Data/btc_usdt.csv";
    double initialBalance = 100000.0;

    // Handle command-line arguments: optional CSV and initial balance
    if (argc > 1) {
        dataFile = argv[1];
    }
    if (argc > 2) {
        try {
            initialBalance = std::stod(argv[2]);
        } catch (...) {
            std::cerr << "Invalid initial balance input. Using default: $100000.00\n";
        }
    }

    // Validate file existence
    if (!std::filesystem::exists(dataFile)) {
        std::cerr << " Error: Market data file not found: " << dataFile << "\n";
        return 1;
    }

    try {
        MarketData market(dataFile);
        RSIStrategy strategy;
        Portfolio portfolio;
        Execution_engine executor;
        Simulator simulator;

        // Optional: Set the initial balance (requires modifying Simulator or Portfolio API)
        portfolio.setEquity(initialBalance);

        std::cout << " Starting Backtest with:\n";
        std::cout << "   - Data file: " << dataFile << "\n";
        std::cout << "   - Initial balance: $" << initialBalance << "\n";
        std::cout << "==============================\n";

        simulator.run(market, strategy, portfolio, executor);

        std::cout << "==============================\n";
        std::cout << "✅ Backtest complete.\n";

    } catch (const std::exception& e) {
        std::cerr << " Simulation error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
