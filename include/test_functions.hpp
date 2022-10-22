#ifndef TEST_FUNCTIONS_HPP
#define TEST_FUNCTIONS_HPP

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


double calculateTestFunc1CosinusPart(const std::vector<double>& args);

double calculateTestFunc2CosinusPart(const std::vector<double>& args);


double testFunc1(std::vector<double> args);


double testFunc2(std::vector<double> args);

#endif