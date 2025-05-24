#include "MarketData.h"
#include <fstream>
#include <sstream>
#include <iostream>

MarketData::MarketData(const std::string& filename) : currentIndex(0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        Bar bar;
        std::string token;

        try {
            getline(ss, bar.timestamp, ',');
            getline(ss, token, ','); bar.open = std::stod(token);
            getline(ss, token, ','); bar.high = std::stod(token);
            getline(ss, token, ','); bar.low = std::stod(token);
            getline(ss, token, ','); bar.close = std::stod(token);
            getline(ss, token, ','); bar.volume = std::stod(token);

            bars.push_back(bar);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " (" << e.what() << ")" << std::endl;
        }
    }
}

bool MarketData::hasNext() const {
    return currentIndex < bars.size();
}

Bar MarketData::getNextBar() {
    if (!hasNext()) {
        throw std::out_of_range("No more market data.");
    }
    return bars[currentIndex++];
}
