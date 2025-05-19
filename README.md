# Algorithmic_Trading_Bot_Simulator
This project simulates a fully modular algorithmic trading bot built in C++, using historical data (from Binance via Python) to test a rule-based strategy powered by the Relative Strength Index (RSI). The simulator is equipped with a basic risk management module and is designed to be self-tuning and extendable for future strategies.

<br>
RSI-Based Strategy:

    Buys when RSI < 30 (oversold).

    Sells when RSI > 70 (overbought).

Risk Management:

    Prevents trades if the loss exceeds a configurable stop-loss (default: 20%).

Simulation Engine:

    Loads historical OHLCV market data from CSV.

    Simulates trade execution, portfolio management, and equity tracking.

Python Binance Integration (for data collection):

    Historical candle data is downloaded using the Python Binance API.

    Data is saved as CSV files for C++ to ingest.
