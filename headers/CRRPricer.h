#pragma once

#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "AmericanOption.h"
#include "BinaryTree.h"


class CRRPricer {
public:
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);
    CRRPricer(Option* option, int depth, double asset_price, double rate, double volatility);
    
    double operator()(bool closed_form = true);
    void compute();
    double get(int level, int index) const;
    bool getExercise(int level, int index) const;

private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _rate;

    BinaryTree<double> _prices;
    BinaryTree<double> _values;
    BinaryTree<bool> _exercise;
    bool _computed;
    
    double powInt(double base, int exponent) const;
    double combination(int n, int k) const;
};
