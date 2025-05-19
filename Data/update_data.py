import os
import csv
from binance.client import Client
from datetime import datetime, timedelta
from dotenv import load_dotenv

load_dotenv()

def fetch_klines():
    """Fetch and save BTC/USDT hourly data"""
    try:
        api_key = os.getenv('BINANCE_API_KEY')
        api_secret = os.getenv('BINANCE_API_SECRET')
        if not api_key or not api_secret:
            raise EnvironmentError("Missing Binance API credentials in .env file")

        client = Client(api_key, api_secret)
        os.makedirs('data', exist_ok=True)

        end_date = datetime.utcnow()
        start_date = end_date - timedelta(days=7)

        klines = client.get_historical_klines(
            "BTCUSDT",
            Client.KLINE_INTERVAL_1HOUR,
            start_str=start_date.strftime("%d %b %Y %H:%M:%S"),
            end_str=end_date.strftime("%d %b %Y %H:%M:%S")
        )

        with open("data/sample.csv", "w", newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(["timestamp", "open", "high", "low", "close", "volume"])
            for k in klines:
                ts = datetime.utcfromtimestamp(k[0] / 1000).isoformat()
                writer.writerow([
                    ts,
                    float(k[1]),
                    float(k[2]),
                    float(k[3]),
                    float(k[4]),
                    float(k[5])
                ])

        print(f"✅ Data updated successfully: {len(klines)} records written to 'data/sample.csv'")
        return True

    except Exception as e:
        print(f"❌ Error fetching data: {e}")
        return False

if __name__ == "__main__":
    fetch_klines()
