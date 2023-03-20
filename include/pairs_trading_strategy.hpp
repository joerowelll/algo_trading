#ifndef PAIRS_TRADING_STRATEGY_HPP
#define PAIRS_TRADING_STRATEGY_HPP

#include <iostream>
#include <vector>
#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"
#include "Contract.h"
#include "Order.h"
#include "OrderState.h"
#include "Execution.h"
#include "ScannerSubscription.h"
#include "CommissionReport.h"
#include "AccountSummaryTags.h"
#include "api/IBApiClient.h"
#include "api/EReaderSignal.h"

using namespace std;
using namespace IbApi;
using namespace IbApi::Api;

class MyEWrapper : public EWrapper {
public:
    MyEWrapper() {}

    void tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attribs) override;

    double calculateMean(vector<double>& data);

    double calculateStandardDeviation(vector<double>& data, double mean);

private:
    double price1 = 0;
    double price2 = 0;
    vector<double> ratios;
};

#endif /* PAIRS_TRADING_STRATEGY_HPP */