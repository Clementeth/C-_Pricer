#include "AsianPutOption.h"


AsianPutOption::AsianPutOption(const std::vector<double>& time_steps, double strike)
    : AsianOption(time_steps) {

    _strike = strike;
    
}


double AsianPutOption::payoff(double spot) const {

    double payoff_value = 0.0;
    if (spot < _strike) {
        payoff_value = _strike - spot;
    }
    return payoff_value;

}
