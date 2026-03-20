#include "MT.h"

MT::MT() {
    std::random_device rd;
    _gen.seed(rd());
}

MT& MT::instance() {
    static MT mt_instance;
    return mt_instance;
}

double MT::rand_unif() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(instance()._gen);
}

double MT::rand_norm() {
    std::normal_distribution<double> dist(0.0, 1.0);
    return dist(instance()._gen);
}
