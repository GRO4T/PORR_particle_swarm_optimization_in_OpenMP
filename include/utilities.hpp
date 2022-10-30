#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>
#include <chrono>

#define  OPENMP_ENABLED // wykomentować jeśli nie chcemy zrównoleglenia

using Point = std::vector<double>;

struct SearchResult
{
    Point x;
    double result;
    long int time;
};


#endif