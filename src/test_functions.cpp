#include "../include/test_functions.hpp"


double calculateTestFunc1CosinusPart(const std::vector<double>& args) {
    if (args.size() == 0)
        return 0;    
    
    int i = 1;
    double res = std::cos(args[0] / (double)1);
    int N = args.size();
    // #pragma omp parallel for shared(N) private(i) reduction(* : res) //<- coś jest nie tak bo to spowalnia liczenie
    for (i = 2; i < N + 1; ++i) {
        res *= std::cos(args[i-1] / i); 
    }
    return res;
}

double calculateTestFunc2CosinusPart(const std::vector<double>& args) {
    double res = 0;
    for (int i = 0; i < args.size(); ++i) {
        res += std::cos(2 * M_PI * args[i]); 
    }
    return res;
}


double testFunc1(std::vector<double> args) {
    double sum_of_x_squared = std::accumulate(args.begin(), args.end(), 0, square<double>());
    double cosinus_part = calculateTestFunc1CosinusPart(args);
    return 1/40.f * sum_of_x_squared + 1 - cosinus_part;
}


double testFunc2(std::vector<double> args) {
    int n = args.size();
    double sum_of_x_squared = std::accumulate(args.begin(), args.end(), 0, square<double>());
    double first_exponent_part = 20 * std::exp(-0.2f * std::sqrt(sum_of_x_squared / n));
    double second_exponent_part = std::exp(calculateTestFunc2CosinusPart(args) / n);
    return first_exponent_part - second_exponent_part + 20 + std::exp(1.0);
}