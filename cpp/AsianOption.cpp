#include "AsianOption.h"

#include <cstddef>

double check_time_steps(const std::vector<double>& time_steps) {
    double last = 0.0;

    if (!time_steps.empty()) {
        last = time_steps.back();
    }

    return last;
}

AsianOption::AsianOption(const std::vector<double>& time_steps)
    : Option(check_time_steps(time_steps)) {

    _time_steps = time_steps;

}


const std::vector<double>& AsianOption::getTimeSteps() const {
    return _time_steps;
}


double AsianOption::payoffPath(const std::vector<double>& spots) const {
    double sum = 0.0;
    double average = 0.0;

    if (spots.empty()) {
        return 0.0;
    }

    for (std::size_t i = 0; i < spots.size(); i++) {
        sum = sum + spots[i];
    }
    
    average = sum / spots.size();
    return payoff(average);
}

bool AsianOption::isAsianOption() const  {
    return true;
}
