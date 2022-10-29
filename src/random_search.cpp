#include "random_search.hpp"
#include "test_functions.hpp"
#include "utilities.hpp"
#include "plots.hpp"

#include <float.h>
#include <cassert>
#include <chrono>
#include <omp.h>

thread_local std::mt19937 RandomSearch::random_engine;

void RandomSearch::setSeed(int seed /*= time(NULL)*/)
{
    random_engine = std::mt19937(seed);
}

SearchResult RandomSearch::search(
    std::function<double(Point)> objective_func,
    Point& min_x,
    Point& max_x,
    size_t iterations
)
{
    assert((min_x.size() == max_x.size()) && "Different dimensions in range of domain");

    omp_set_num_threads(8); // TODO w utilities jest stała określająca liczbę wątków

    auto begin = std::chrono::steady_clock::now();

    double best_result = DBL_MAX;
    Point best_position;

    // ustawienie zakresu losowania
    std::vector<std::uniform_real_distribution<double>> unifs;
    for(unsigned int i = 0; i < min_x.size(); ++i)
    {
        unifs.push_back(std::uniform_real_distribution<double>(min_x[i], max_x[i]));
    }

    #ifdef OPENMP_ENABLED
        #pragma omp parallel for shared(best_result, best_position, unifs) num_threads(OMP_NUM_THREADS)
    #endif
    for(std::size_t i = 0; i < iterations; ++i)
    {
        std::vector<double> random_point;
        for(auto unif : unifs)
        {
            random_point.push_back(unif(random_engine));
        }

        double result = objective_func(random_point);

        #ifdef OPENMP_ENABLED
        #pragma omp critical
        {
        #endif
            if(result < best_result)
            {
                best_result = result;
                best_position = random_point;
            }
        #ifdef OPENMP_ENABLED
        }
        #endif
    }

    auto end = std::chrono::steady_clock::now();
    auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();

    return SearchResult({best_position, best_result, exec_time});
}

void RandomSearch::plot(
    std::function<double(Point)> objective_func,
    double min_x,
    double max_x,
    size_t iterations,
    double animation_speed  
) {
    double best_result = DBL_MAX;
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



