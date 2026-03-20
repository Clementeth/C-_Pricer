#include "BlackScholesPricer.h"

#include <cmath>


BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double spot, double rate, double volatility) {
    _option = option;
    _spot = spot;
    _rate = rate;
    _volatility = volatility;
    
}


double BlackScholesPricer::normalCdf(double x) const {

    double result = 0.5 * std::erfc(-x / std::sqrt(2.0));
    return result;

}

double BlackScholesPricer::normalPdf(double x) const {
    double coeff;
    coeff = 1.0 / std::sqrt(2.0 * 3.1415926535);
    double expo;
    expo = std::exp(-0.5*x*x);
    double value;
    value = coeff * expo;
    return value;
}


double BlackScholesPricer::operator()() {
    double T = _option->getExpiry();
    double strike = _option->strike();

    double sqrtT = std::sqrt(T);
    double log_term = std::log(_spot / strike);
    double vol_sq = _volatility * _volatility;
    double numerator = log_term + (_rate + 0.5*vol_sq) * T;
    double denominator = _volatility*sqrtT;
    double d1 = numerator / denominator;
    double d2 = d1 - _volatility*sqrtT;

    EuropeanDigitalOption* digital_ptr = dynamic_cast<EuropeanDigitalOption*>(_option);

    if (digital_ptr != nullptr) {
        double discount = std::exp(-_rate * T);
        if (_option->GetOptionType() == EuropeanVanillaOption::optionType::call) {
            double nd2 = normalCdf(d2);
            return discount * nd2;
        } else {
            double nd2 = normalCdf(-d2);
            return discount * nd2;
        }
    }

    if (_option->GetOptionType() == EuropeanVanillaOption::optionType::call) {
        double nd1 = normalCdf(d1);  
        double nd2 = normalCdf(d2);
        return _spot * nd1 - strike * std::exp(-_rate * T) * nd2;
    }

    double nd1 = normalCdf(-d1);
    double nd2 = normalCdf(-d2);

    return strike * std::exp(-_rate * T) * nd2 - _spot * nd1;
}


double BlackScholesPricer::delta() {
    double T = _option->getExpiry();
    double strike = _option->strike();
    double sqrtT = std::sqrt(T);
    double log_term = std::log(_spot / strike);
    double vol_sq = _volatility * _volatility;
    double numerator = log_term + (_rate + 0.5 * vol_sq) * T;
    double denominator = _volatility * sqrtT;
    double d1 = numerator / denominator;

    EuropeanDigitalOption* digital_ptr = dynamic_cast<EuropeanDigitalOption*>(_option);
    if (digital_ptr != nullptr) {
        double discount = std::exp(-_rate * T);
        double pdf_d2 = normalPdf(d1 - _volatility * sqrtT);
        double delta_value = discount * pdf_d2 / (_spot * _volatility * sqrtT);
        if (_option->GetOptionType() == EuropeanVanillaOption::optionType::call) {
            return delta_value;
        } else {
            return -delta_value;
        }
    }

    if (_option->GetOptionType() == EuropeanVanillaOption::optionType::call) {
        return normalCdf(d1);
    }

    return normalCdf(d1) - 1.0;
}
