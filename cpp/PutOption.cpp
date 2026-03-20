#include "PutOption.h"


PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}


PutOption::~PutOption() {}


double PutOption::payoff(double spot) const {
    double strike_value = strike();

    if (spot < strike_value) {
        return strike_value - spot;
    }
    
    return 0.0;    
}

EuropeanVanillaOption::optionType PutOption::GetOptionType() const {
    return optionType::put;    
}
