#include "pairs_trading_strategy.hpp"

void MyEWrapper::tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attribs) {
    if (field == TickType::LAST_PRICE) {
        if (tickerId == 1) {
            price1 = price;
        } else if (tickerId == 2) {
            price2 = price;
        }
        if (price1 != 0 && price2 != 0) {
            double currentRatio = price1 / price2;
            ratios.push_back(currentRatio);
            if (ratios.size() > 30) {
                double mean = calculateMean(ratios);
                double stdev = calculateStandardDeviation(ratios, mean);
                if (currentRatio < mean - 2 * stdev) {
                    // Enter into long position on stock2 and short position on stock1
                    cout << "Entering into long position on stock2 and short position on stock1." << endl;
                } else if (currentRatio > mean + 2 * stdev) {
                    // Enter into long position on stock1 and short position on stock2
                    cout << "Entering into long position on stock1 and short position on stock2." << endl;
                }
            }
        }
    }
}

double MyEWrapper::calculateMean(vector<double>& data) {
    double sum = 0;
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    return sum / data.size();
}

double MyEWrapper::calculateStandardDeviation(vector<double>& data, double mean) {
    double sum = 0;
    for (int i = 0; i < data.size(); i++) {
        sum += pow(data[i] - mean, 2);
    }
    double variance = sum / (data.size() - 1);
    return sqrt(variance);
}

int main(int argc, char** argv) {
    IbApiClient client(make_shared<MyEWrapper>(), make_shared<EReaderSignal>());
    client.connect("127.0.0.1", 7497, 0);

    MyEWrapper& wrapper = dynamic_cast<MyEWrapper&>(client.wrapper());

    wrapper.m_contract1.symbol = "GOOGL";
    wrapper.m_contract1.secType = "STK";
    wrapper.m_contract1.exchange = "SMART";
    wrapper.m_contract1
    wrapper.m_contract1.currency = "USD";

    wrapper.m_contract2.symbol = "AAPL";
    wrapper.m_contract2.secType = "STK";
    wrapper.m_contract2.exchange = "SMART";
    wrapper.m_contract2.currency = "USD";

    client.reqMarketDataType(1);
    client.reqMktData(1, wrapper.m_contract1, "", false, false, TagValueListSPtr());
    client.reqMktData(2, wrapper.m_contract2, "", false, false, TagValueListSPtr());

    client.run();

    return 0;
}