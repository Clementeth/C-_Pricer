#pragma once

#include "AsianOption.h"


class AsianPutOption : public AsianOption {
public:
    AsianPutOption(const std::vector<double>& time_steps, double strike);

    double payoff(double spot) const override;

private:
    double _strike;
};
