#include "MarketData.h"
#include <fstream>
#include <sstream>

std::vector<Candle> MarketData::loadCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Candle> candles;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Candle c;
        std::string token;

        std::getline(ss, c.timestamp, ',');
        std::getline(ss, token, ','); c.open = std::stod(token);
        std::getline(ss, token, ','); c.high = std::stod(token);
        std::getline(ss, token, ','); c.low = std::stod(token);
        std::getline(ss, token, ','); c.close = std::stod(token);
        std::getline(ss, token, ','); c.volume = std::stod(token);

        candles.push_back(c);
    }

    return candles;
}
