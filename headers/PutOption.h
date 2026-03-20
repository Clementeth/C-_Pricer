#pragma once

#include "EuropeanVanillaOption.h"


class PutOption : public EuropeanVanillaOption {
public:
    PutOption(double expiry, double strike);
    ~PutOption() override;

    double payoff(double spot) const override;
    optionType GetOptionType() const override;
};
