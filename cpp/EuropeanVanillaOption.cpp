#include "EuropeanVanillaOption.h"


EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry) {
    _strike = strike;
    
    if (_strike < 0.0) {
        _strike = 0.0;
    }    
}


EuropeanVanillaOption::~EuropeanVanillaOption() {


}


double EuropeanVanillaOption::strike() const {
    return _strike;    
}
