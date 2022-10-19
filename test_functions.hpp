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


float testFunc1(std::vector<float> args) {
    float sum_of_x_squared = std::accumulate(args.begin(), args.end(), 0, square<float>());
    float cosinus_part = calculateTestFunc1CosinusPart(args);
    return 1/40.f * sum_of_x_squared + 1 - cosinus_part;
}

