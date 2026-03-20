#pragma once

#include "EuropeanVanillaOption.h"


class EuropeanDigitalOption : public EuropeanVanillaOption {
public:
    EuropeanDigitalOption(double expiry, double strike);
    ~EuropeanDigitalOption() override;
};


class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiry, double strike);
    ~EuropeanDigitalCallOption() override;

    double payoff(double spot) const override;
    optionType GetOptionType() const override;
};


class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike);
    ~EuropeanDigitalPutOption() override;

    double payoff(double spot) const override;
    optionType GetOptionType() const override;
};
