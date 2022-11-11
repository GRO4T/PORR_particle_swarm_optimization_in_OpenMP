#ifndef RANDOM_SEARCH
#define RANDOM_SEARCH

#include <ctime>
#include <random>
#include <functional>
#include <future>

#include "utilities.hpp"

class RandomSearch
{
public:
    RandomSearch(
        std::function<double(Point)> &objective_func,
        size_t n,
        int threads = 4,
        double min_x = -40,
        double max_x = 40
    );

    void setSeed(int thread_id);

    SearchResult search(size_t iterations);

    void plot(size_t iterations, double animation_speed = 1.0 / 0.01);

    static thread_local std::mt19937 random_engine;

private:
    std::function<double(Point)> objective_func;
    size_t n;
    int threads;
    double min_x;
    double max_x;
    uint time_seed;
};

#endif