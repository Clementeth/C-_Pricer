#include "CallOption.h"


CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}


CallOption::~CallOption() {}


double CallOption::payoff(double spot) const {
    double strike_value = strike();
    double payoff_value = 0.0;
    if (spot > strike_value) {
        payoff_value = spot - strike_value;
    }
    return payoff_value;    
}

EuropeanVanillaOption::optionType CallOption::GetOptionType() const {
    return optionType::call;    
}
