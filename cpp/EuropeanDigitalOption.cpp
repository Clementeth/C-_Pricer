#include "EuropeanDigitalOption.h"


EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {}


EuropeanDigitalOption::~EuropeanDigitalOption() {}


EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}


EuropeanDigitalCallOption::~EuropeanDigitalCallOption() {}


double EuropeanDigitalCallOption::payoff(double spot) const {
    if (spot >= strike()) {
        return 1.0;
    }
    return 0.0;
}


EuropeanVanillaOption::optionType EuropeanDigitalCallOption::GetOptionType() const {
    return optionType::call;
}


EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}


EuropeanDigitalPutOption::~EuropeanDigitalPutOption() {}


double EuropeanDigitalPutOption::payoff(double spot) const {
    if (spot <= strike()) {
        return 1.0;
    }
    return 0.0;
}


EuropeanVanillaOption::optionType EuropeanDigitalPutOption::GetOptionType() const {
    return optionType::put;
}
