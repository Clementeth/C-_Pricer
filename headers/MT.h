#pragma once

#include <random>

// Singleton 
class MT {

public:
    static double rand_unif();
    static double rand_norm();

private:
    MT();
    static MT& instance();
    std::mt19937 _gen;
    
};
