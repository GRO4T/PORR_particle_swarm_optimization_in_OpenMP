#include "random_search.hpp"
#include "test_functions.hpp"
#include "utilities.hpp"
#include "plots.hpp"

#include <cfloat>
#include <cassert>
#include <chrono>
#include <omp.h>

thread_local std::mt19937 RandomSearch::random_engine;

RandomSearch::RandomSearch(
    std::function<double(Point)> &objective_func,
    size_t n,
    int threads,
    double min_x,
    double max_x,
    int seed
):      objective_func(objective_func),
        n(n),
        threads(threads),
        min_x(min_x),
        max_x(max_x) {
    setSeed(seed);
}

void RandomSearch::setSeed(int seed /*= time(NULL)*/)
{
    random_engine = std::mt19937(seed);
}

SearchResult RandomSearch::search(size_t iterations) {
    omp_set_num_threads(threads);

    auto begin = std::chrono::steady_clock::now();

    auto best_result = DBL_MAX;
    Point best_position;

    // ustawienie zakresu losowania
    std::vector<std::uniform_real_distribution<double>> unifs;
    for(size_t i = 0; i < n; ++i)
    {
        unifs.emplace_back(min_x, max_x);
    }

    #ifdef OPENMP_ENABLED
        #pragma omp parallel for shared(best_result, best_position, unifs) 
    #endif
    for(std::size_t i = 0; i < iterations; ++i)
    {
        std::vector<double> current_point;
        for(auto unif : unifs)
        {
            current_point.push_back(unif(random_engine));
        }

        double result = objective_func(current_point);

        #ifdef OPENMP_ENABLED
        #pragma omp critical
        {
        #endif
            if(result < best_result)
            {
                best_result = result;
                best_position = current_point;
            }
        #ifdef OPENMP_ENABLED
        }
        #endif
    }

    auto end = std::chrono::steady_clock::now();
    auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();

    return SearchResult({best_position, best_result, exec_time});
}

void RandomSearch::plot(size_t iterations, double animation_speed) {
    assert(n == 2);

    auto best_result = DBL_MAX;
    Point best_position;

    // ustawienie zakresu losowania
    std::vector<std::uniform_real_distribution<double>> unifs {
        std::uniform_real_distribution<double>(min_x, max_x),
        std::uniform_real_distribution<double>(min_x, max_x)
    };

    for(std::size_t i = 0; i < iterations; ++i)
    {
        plotClear();

        std::vector<double> random_point;
        for(auto unif : unifs)
        {
            random_point.push_back(unif(random_engine));
        }

        double result = objective_func(random_point);

        if(result < best_result)
        {
            best_result = result;
            best_position = random_point;
        }

        std::cout << "-------------------------------" << std::endl;
        std::cout << "iteration: " << i << std::endl;
        std::cout << "best_result: " << best_result << std::endl;
        std::cout << "best_position: (" << best_position[0] << ", " << best_position[1] << ")" << std::endl;

        plotContourWithBestAndCurrentPoint(objective_func, best_position, random_point, min_x, max_x, animation_speed);
    }
}



