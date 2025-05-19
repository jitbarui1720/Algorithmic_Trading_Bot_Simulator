#include "MarketData.h"
#include <fstream>
#include <sstream>

MarketData::MarketData(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        std::stringstream ss(line);
        Bar bar;
        std::string token;
        getline(ss, bar.timestamp, ',');
        getline(ss, token, ','); bar.open = std::stod(token);
        getline(ss, token, ','); bar.high = std::stod(token);
        getline(ss, token, ','); bar.low = std::stod(token);
        getline(ss, token, ','); bar.close = std::stod(token);
        getline(ss, token, ','); bar.volume = std::stod(token);
        bars.push_back(bar);
    }
}

bool MarketData::hasNext() const {
    return currentIndex < bars.size();
}

Bar MarketData::getNextBar() {
    return bars[currentIndex++];
}
