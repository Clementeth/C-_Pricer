#include "AmericanOption.h"

AmericanOption::AmericanOption(double expiry, double strike)
    : Option(expiry) {
    _strike = strike;
}

AmericanOption::~AmericanOption() {}

double AmericanOption::getStrike() const {
    return _strike;
}

bool AmericanOption::isAmericanOption() const {
    return true;
}

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}

AmericanCallOption::~AmericanCallOption() {}

double AmericanCallOption::payoff(double spot) const {
    double payoff_value = 0.0;
    if (spot > _strike) {
        payoff_value = spot - _strike;
    }
    return payoff_value;
}

AmericanOption::optionType AmericanCallOption::GetOptionType() const {
    return optionType::call;
}

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}

AmericanPutOption::~AmericanPutOption() {}

double AmericanPutOption::payoff(double spot) const {
    double payoff_value = 0.0;
    if (spot < _strike) {
        payoff_value = _strike - spot;
    }
    return payoff_value;
}

AmericanOption::optionType AmericanPutOption::GetOptionType() const {
    return optionType::put;
}
