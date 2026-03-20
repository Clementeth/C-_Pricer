#pragma once

#include "Option.h"
#include <vector>
#include <random>
#include <stdexcept>
#include "MT.h"


class BlackScholesMCPricer {
public:
    BlackScholesMCPricer(Option* option, double spot, double rate, double volatility);

    void generate(int n);
    double operator()();
    std::vector<double> confidenceInterval() const;
    int getNbPaths() const;

private:
    Option* _option;
    double _spot;
    double _rate;
    double _volatility;
    int _nb_paths;
    double _sum_payoff;
    double _sum_payoff_sq;

    double powInt(double base, int exponent) const;
};
