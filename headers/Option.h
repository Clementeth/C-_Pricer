#pragma once

// ajout pour payoffPath
#include <vector>

// Base class for all options
class Option {
public:
    explicit Option(double expiry);
    virtual ~Option();

    double getExpiry() const;
    virtual double payoff(double spot) const = 0;
    virtual double payoffPath(const std::vector<double>& spots) const;
    bool isAsianOption() const;
    virtual bool isAmericanOption() const;

private:
    double _expiry;
};
