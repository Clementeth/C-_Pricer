#include "Option.h"
#include <vector>


Option::Option(double expiry) {
    _expiry = expiry;
    
}


Option::~Option() {}


double Option::getExpiry() const {
    return _expiry;    
}


double Option::payoffPath(const std::vector<double>& spots) const {
    if (spots.empty()) {
        return 0.0;
    }else{
        double last;
        last = spots.back();
        return payoff(last);
    }

}

bool Option::isAsianOption() const {
    return false;
}

bool Option::isAmericanOption() const {
    return false;
}
