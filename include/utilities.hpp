#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>
#include <chrono>

#define LOOPS_NUMBER 1000000

#define  OPENMP_ENABLED // wykomentować jeśli nie chcemy zrównoleglenia

#define OMP_NUM_THREADS 4

using Point = std::vector<double>;

struct SearchResult
{
    Point x;
    double result;
    unsigned long long time;
};


#endif