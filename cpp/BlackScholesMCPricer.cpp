#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <omp.h> //OpenMP for parallelization. Please make sure OpenMP is enabled in your environment and that you're not in Debug mode (it makes it slower than sequential)
#include <cmath>


BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double spot, double rate, double volatility) {
    _option = option;
    _spot = spot;
    _rate = rate;
    _volatility = volatility;
    _nb_paths = 0;
    _sum_payoff = 0.0;
    _sum_payoff_sq = 0.0;
}


double BlackScholesMCPricer::powInt(double base, int exponent) const {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result = result * base;
    }
    return result;
}

void BlackScholesMCPricer::generate(int n) {
    double T = _option->getExpiry();

    std::vector<double> time_steps;
    AsianOption* asian_ptr = dynamic_cast<AsianOption*>(_option);
    if (asian_ptr != nullptr) {
        time_steps = asian_ptr->getTimeSteps();
    }
    else {
        time_steps.push_back(T);
    }

    const size_t m = time_steps.size();

    // Thread-local reusable buffers
    static thread_local std::vector<double> path_spots;
    static thread_local std::vector<double> dt;
    static thread_local std::vector<double> sqrt_dt;

    // Precompute dt and sqrt(dt) ONCE (read-only afterwards)
    std::vector<double> dt_shared(m);
    std::vector<double> sqrt_dt_shared(m);

    double previous_time = 0.0;
    for (size_t i = 0; i < m; ++i) {
        dt_shared[i] = time_steps[i] - previous_time;
        if (dt_shared[i] < 0.0) dt_shared[i] = 0.0;
        sqrt_dt_shared[i] = std::sqrt(dt_shared[i]);
        previous_time = time_steps[i];
    }

    const double vol = _volatility;
    const double drift_coeff = _rate - 0.5 * vol * vol;

    double local_sum = 0.0;
    double local_sumsq = 0.0;

#pragma omp parallel reduction(+:local_sum, local_sumsq)
    {
        // Each thread initializes its own buffers
        path_spots.resize(m);
        dt = dt_shared;
        sqrt_dt = sqrt_dt_shared;

#pragma omp for
        for (int path = 0; path < n; ++path) {

            double spot_path = _spot;

            for (size_t step = 0; step < m; ++step) {
                double z = MT::rand_norm(); // must be thread-safe
                spot_path *= std::exp(
                    drift_coeff * dt[step] + vol * sqrt_dt[step] * z
                );
                path_spots[step] = spot_path;
            }

            double payoff_value = _option->payoffPath(path_spots);
            local_sum += payoff_value;
            local_sumsq += payoff_value * payoff_value;
        }
    }

    _sum_payoff += local_sum;
    _sum_payoff_sq += local_sumsq;
    _nb_paths += n;
}




double BlackScholesMCPricer::operator()() {
    if (_nb_paths == 0) {
        throw std::runtime_error("No paths generated");
    }
    double mean = _sum_payoff / double(_nb_paths);
    double T = _option->getExpiry();
    double discount = std::exp(-_rate*T);
    double price = discount*mean;
    return price;
}


std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    std::vector<double> ci;
    if (_nb_paths == 0) {
        ci.push_back(0.0);
        ci.push_back(0.0);
        return ci;
    }
    double mean = _sum_payoff / double(_nb_paths);
    double mean_sq = _sum_payoff_sq / double(_nb_paths);
    double variance = mean_sq - mean * mean;
    if (variance < 0.0) {
        variance = 0.0;
    }
    double stddev = std::sqrt(variance);
    double T = _option->getExpiry();
    double discount = std::exp(-_rate * T);

    double margin = 1.96 * stddev / std::sqrt(double(_nb_paths));
    double lower = discount * (mean - margin);
    double upper = discount * (mean + margin);
    ci.push_back(lower);
    ci.push_back(upper);
    return ci;
}


int BlackScholesMCPricer::getNbPaths() const {
    return _nb_paths;
}
