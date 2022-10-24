#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>
#include <chrono>

#define LOOPS_NUMBER 1000000

struct SearchResult
{
    std::vector<double>x;
    double result;
    unsigned long long time;
};

SearchResult createSearchResult(std::vector<double>x, double result);


#endif