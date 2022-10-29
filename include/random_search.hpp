#ifndef RANDOM_SEARCH
#define RANDOM_SEARCH

#include <time.h>
#include <random>
#include <functional>
#include <future>

#include "utilities.hpp"

class RandomSearch
{
public:
    static void setSeed(int seed = time(NULL));
    static SearchResult search(
        std::function<double(Point)> objective_func,
        Point& min_x,
        Point& max_x,
        size_t iterations
    );
    static void plot(
        std::function<double(Point)> objective_func,
        double min_x,
        double max_x,
        size_t iterations,
        double animation_speed = 1.0 / 0.01
    );
    static thread_local std::mt19937 random_engine;
};


#endif