#include "CRRPricer.h"

#include <cmath>
#include <stdexcept>


CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) {
    if (option->isAsianOption()) {
        throw std::invalid_argument("CRRPricer does not support Asian options.");
    }

    _option = option;
    _depth = depth;
    _asset_price = asset_price;
    _up = up;
    _down = down;
    _rate = interest_rate;
    _computed = false;

    if (!(_down < _rate && _rate < _up)) {
        throw std::invalid_argument("Arbitrage condition violated: need down < rate < up");
    }

    _prices.setDepth(_depth);
    _values.setDepth(_depth);
    _exercise.setDepth(_depth);
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double rate, double volatility) {
    if (option->isAsianOption()) {
        throw std::invalid_argument("CRRPricer does not support Asian options.");
    }

    _option = option;
    _depth = depth;
    _asset_price = asset_price;
    _computed = false;

    double T = _option->getExpiry();
    double dt = depth > 0 ? T / depth : 0.0;
    double sqrt_dt = std::sqrt(dt);

    _up = std::exp((rate + 0.5*volatility*volatility)*dt + volatility*sqrt_dt) - 1.0;
    _down = std::exp((rate + 0.5*volatility*volatility)*dt - volatility*sqrt_dt) - 1.0;
    _rate = std::exp(rate * dt) - 1.0;

    if (!(_down < _rate && _rate < _up)) {
        throw std::invalid_argument("Arbitrage condition violated: need down < rate < up");
    }

    _prices.setDepth(_depth);
    _values.setDepth(_depth);
    _exercise.setDepth(_depth);
}


double CRRPricer::powInt(double base, int exponent) const {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result = result * base;
    }
    return result;
}


double CRRPricer::combination(int n, int k) const {
    if (k < 0 || k > n) {
        return 0.0;
    }
    if (k == 0 || k == n) {
        return 1.0;
    }
    int kk = k;
    if (kk > n - kk) {
        kk = n - kk;
    }
    double result = 1.0;
    for (int i = 1; i <= kk; i++) {
        double numerator = n - (kk - i);
        double denominator = i;
        result = result * (numerator / denominator);
    }
    return result;    
}


void CRRPricer::compute() {
    double one_plus_up = 1.0 + _up;
    double one_plus_down = 1.0 + _down;

    for (int i = 0; i <= _depth; i++) {
        double node_price = _asset_price * powInt(one_plus_up, i) * powInt(one_plus_down, _depth - i);
        _prices.setNode(_depth, i, node_price);
        double payoff_value = _option->payoff(node_price);
        _values.setNode(_depth, i, payoff_value);
        _exercise.setNode(_depth, i, false);
    }

    double q;
    double numerator_q, denominator_q;
    numerator_q = _rate - _down;
    denominator_q = _up - _down;
    q = numerator_q / denominator_q;


    for (int level = _depth - 1; level >= 0; level--) {
        for (int i = 0; i <= level; i++) {
            double next_up, next_down, value;
            next_up = _values.getNode(level + 1, i + 1);
            next_down = _values.getNode(level + 1, i);
            double numerator_value, denominator_value;
            numerator_value = q * next_up + (1.0 - q) * next_down;
            denominator_value = 1.0 + _rate;
            value = numerator_value / denominator_value;
            _values.setNode(level, i, value);
            double price_here;
            price_here = _asset_price * powInt(one_plus_up, i) * powInt(one_plus_down, level - i);
            _prices.setNode(level, i, price_here);

            AmericanOption* am_ptr;
            am_ptr = dynamic_cast<AmericanOption*>(_option);
            if (am_ptr != nullptr) {
                double exercise;
                exercise = _option->payoff(price_here);
                bool exercise_now;
                exercise_now = exercise >= value;
                _exercise.setNode(level, i, exercise_now);
                if (exercise_now) {
                    value = exercise;
                }
                _values.setNode(level, i, value);
            } else {
                _exercise.setNode(level, i, false);
            }
        }
    }
    _computed = true;
}


double CRRPricer::get(int level, int index) const {
    return _values.getNode(level, index);
}

bool CRRPricer::getExercise(int level, int index) const {
    return _exercise.getNode(level, index);
}


double CRRPricer::operator()(bool closed_form) {
    AmericanOption* am_ptr = dynamic_cast<AmericanOption*>(_option);
    if (am_ptr != nullptr) {
        if (!_computed) {
            compute();
        }
        return _values.getNode(0, 0);
    }

    if (closed_form) { // closed-form formula
        double q = (_rate - _down) / (_up - _down);
        double sum = 0.0;
        for (int i = 0; i <= _depth; i++) {
            double comb, prob, spot, term;
            comb = combination(_depth, i);
            prob = powInt(q, i)*powInt(1.0 - q, _depth - i);
            spot = _asset_price*powInt(1.0 + _up, i)*powInt(1.0 + _down, _depth - i);
            term = comb*prob*_option->payoff(spot);
            sum = sum + term;
        }
        double discount;
        discount = powInt(1.0 + _rate, _depth);
        double price;
        price = sum / discount;
        return price;
    }
    else {  
        if (!_computed) {
            compute();        
        }
        return _values.getNode(0, 0);
    }

}
