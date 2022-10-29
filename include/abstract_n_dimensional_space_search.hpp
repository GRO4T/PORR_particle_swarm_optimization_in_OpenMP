#ifndef ABSTRACT_SEARCH_HPP
#define ABSTRACT_SEARCH_HPP

#include <time.h>

#include "utilities.hpp"

class AbstractNDimensionalSpaceSearch {
public:
    AbstractNDimensionalSpaceSearch(double min_x, double max_x, int seed = time(NULL))
        : min_x(min_x), max_x(max_x) {
        setSeed(seed);
    }

    virtual ~AbstractNDimensionalSpaceSearch() {}
    virtual void setSeed(int seed = time(NULL)) = 0;
    virtual SearchResult getBestAfterNIterations(const size_t iterations) = 0;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual SearchResult getCurrentBest() = 0;

    virtual void plotCurrentState() = 0; 

private:
    double min_x;
    double max_x;
};

#endif