#pragma once

#include "AsianOption.h"


class AsianCallOption : public AsianOption {
public:
    AsianCallOption(const std::vector<double>& time_steps, double strike);

    double payoff(double spot) const override;

private:
    double _strike;
};
