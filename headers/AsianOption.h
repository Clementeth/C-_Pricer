#pragma once

#include "Option.h"
#include <vector>


class AsianOption : public Option {
public:
    explicit AsianOption(const std::vector<double>& time_steps);

    const std::vector<double>& getTimeSteps() const;
    double payoffPath(const std::vector<double>& spots) const override;
    bool isAsianOption() const;


protected:
    std::vector<double> _time_steps;
};
