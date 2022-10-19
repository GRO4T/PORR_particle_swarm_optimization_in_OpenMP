#include <vector>
#include <numeric>
#include <cmath>

#include <iostream>


template<typename T>
struct square
{
    T operator()(const T& Left, const T& Right) const
    {   
        return (Left + Right*Right);
    }
};

template<typename T>
struct multiply_cosinus
{
    T operator()(const T& Left, const T& Right) const
    {   
        return (Left * Right*Right);
    }
};


float calculateTestFunc1CosinusPart(const std::vector<float>& args) {
    if (args.size() == 0)
        return 0;    
    
    int i = 1;
    float res = std::cos(args[0] / (float)1);
    for (int i = 2; i < args.size() + 1; ++i) {
        res *= std::cos(args[i-1] / i); 
    }
    return res;
}

float calculateTestFunc2CosinusPart(const std::vector<float>& args) {
    float res = 0;
    for (int i = 0; i < args.size(); ++i) {
        res += std::cos(2 * M_PI * args[i]); 
    }
    return res;
}


float testFunc1(std::vector<float> args) {
    float sum_of_x_squared = std::accumulate(args.begin(), args.end(), 0, square<float>());
    float cosinus_part = calculateTestFunc1CosinusPart(args);
    return 1/40.f * sum_of_x_squared + 1 - cosinus_part;
}


float testFunc2(std::vector<float> args) {
    int n = args.size();
    float sum_of_x_squared = std::accumulate(args.begin(), args.end(), 0, square<float>());
    float first_exponent_part = 20 * std::exp(-0.2f * std::sqrt(sum_of_x_squared / n));
    float second_exponent_part = std::exp(calculateTestFunc2CosinusPart(args) / n);
    return first_exponent_part - second_exponent_part + 20 + std::exp(1.0);
}
