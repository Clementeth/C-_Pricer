#pragma once

#include "Option.h"

class AmericanOption : public Option {
public:
    enum class optionType { call, put };

    AmericanOption(double expiry, double strike);
    ~AmericanOption() override;

    virtual optionType GetOptionType() const = 0;
    double getStrike() const;
    bool isAmericanOption() const override;

protected:
    double _strike;
};


class AmericanCallOption : public AmericanOption {
public:
    AmericanCallOption(double expiry, double strike);
    ~AmericanCallOption() override;

    double payoff(double spot) const override;
    optionType GetOptionType() const override;
};


class AmericanPutOption : public AmericanOption {
public:
    AmericanPutOption(double expiry, double strike);
    ~AmericanPutOption() override;

    double payoff(double spot) const override;
    optionType GetOptionType() const override;
};
