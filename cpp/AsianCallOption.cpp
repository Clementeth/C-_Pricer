#include "AsianCallOption.h"


AsianCallOption::AsianCallOption(const std::vector<double>& time_steps, double strike)
    : AsianOption(time_steps) {
    _strike = strike;
}


double AsianCallOption::payoff(double spot) const {
    double payoff_value = 0.0;
    if (spot > _strike) {
        payoff_value = spot - _strike;
    }
    return payoff_value;
}
