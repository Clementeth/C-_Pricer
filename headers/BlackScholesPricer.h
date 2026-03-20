#pragma once

#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"


class BlackScholesPricer {
public:
    BlackScholesPricer(EuropeanVanillaOption* option, double spot, double rate, double volatility);

    double operator()();
    double delta();


private:
    EuropeanVanillaOption* _option;
    double _spot;
    double _rate;
    double _volatility;

    double normalCdf(double x) const;
    double normalPdf(double x) const;
};
