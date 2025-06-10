import os
import csv
from binance.client import Client
from datetime import datetime, timedelta

def fetch_klines():
    """Fetch and save BTC/USDT 2-minute aggregated data for 1 day"""
    try:
        client = Client("", "")  # Public access
        os.makedirs('data', exist_ok=True)

        end_date = datetime.utcnow()
        start_date = end_date - timedelta(days=1)  # 1 day

        print(f"📥 Fetching 1-minute data from {start_date} to {end_date}")

        # Fetch 1-minute candles (Binance max limit per request is 1000, so we fetch twice)
        klines_1 = client.get_historical_klines(
            "BTCUSDT",
            Client.KLINE_INTERVAL_1MINUTE,
            start_str=start_date.strftime("%d %b %Y %H:%M:%S"),
            limit=1000
        )

        # Get time of last candle in first batch and fetch rest
        last_ts = klines_1[-1][0]
        second_start = datetime.utcfromtimestamp(last_ts / 1000 + 60)

        klines_2 = client.get_historical_klines(
            "BTCUSDT",
            Client.KLINE_INTERVAL_1MINUTE,
            start_str=second_start.strftime("%d %b %Y %H:%M:%S"),
            end_str=end_date.strftime("%d %b %Y %H:%M:%S"),
            limit=1000
        )

        klines = klines_1 + klines_2

        # Group into 2-minute candles
        grouped_klines = []
        for i in range(0, len(klines) - 1, 2):
            c1 = klines[i]
            c2 = klines[i + 1]

            ts = c1[0]
            open_price = float(c1[1])
            high_price = max(float(c1[2]), float(c2[2]))
            low_price = min(float(c1[3]), float(c2[3]))
            close_price = float(c2[4])
            volume = float(c1[5]) + float(c2[5])

            grouped_klines.append([
                datetime.utcfromtimestamp(ts / 1000).isoformat(),
                open_price, high_price, low_price, close_price, volume
            ])

        # Save to CSV
        with open("data/sample.csv", "w", newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(["timestamp", "open", "high", "low", "close", "volume"])
            for row in grouped_klines:
                writer.writerow(row)

        print(f"✅ Data saved: {len(grouped_klines)} 2-minute records written to 'data/sample.csv'")
        return True

    except Exception as e:
        print(f"❌ Error fetching data: {e}")
        return False

if __name__ == "__main__":
    fetch_klines()