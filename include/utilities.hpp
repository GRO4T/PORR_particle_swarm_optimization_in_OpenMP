#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>

#define LOOPS_WITHOUT_EPSILON_TO_STOP 10

struct SearchResult
{
    std::vector<double>x;
    double result;
};

SearchResult createSearchResult(std::vector<double>x, double result);


#endif