#pragma once

#include "Option.h"


class EuropeanVanillaOption : public Option {
public:
    enum class optionType { call, put };

    EuropeanVanillaOption(double expiry, double strike);
    ~EuropeanVanillaOption() override;

    virtual optionType GetOptionType() const = 0;


protected:
    double strike() const;


private:
    double _strike;

    friend class BlackScholesPricer;
    friend class CRRPricer;
};
