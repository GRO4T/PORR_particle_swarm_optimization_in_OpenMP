#include "random_search.hpp"
#include "test_functions.hpp"
#include "utilities.hpp"
#include "plots.hpp"

#include <cfloat>
#include <cassert>
#include <chrono>
#include <omp.h>
#include <iomanip>

thread_local std::mt19937 RandomSearch::random_engine;

RandomSearch::RandomSearch(
    int objective_func_id,
    size_t n,
    int threads,
    double min_x,
    double max_x,
    std::optional<int> snapshot_frequency
):      n(n),
        threads(threads),
        min_x(min_x),
        max_x(max_x),
        snapshot_frequency(snapshot_frequency)
{
    objective_func = objective_func_id == 1 ? testFunc1 : testFunc2;

    time_seed = std::chrono::duration_cast< std::chrono::microseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    if (isSnapshotEnabled()) {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::stringstream datestring;
        datestring << std::put_time(&tm, "%Y%m%d%H%M%S");

        snapshot_name = "func" + std::to_string(objective_func_id)
            + "_random_n" + std::to_string(n) + "_t" + std::to_string(threads) + "_" + datestring.str();
        std::cout << snapshot_name;
    }

}

void RandomSearch::setSeed(int thread_id)
{
        random_engine = std::mt19937(time_seed + thread_id);
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
        #pragma omp parallel
    {
        setSeed(omp_get_thread_num());
    }
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

        stateSnapshot(int(i), best_result);
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

void RandomSearch::stateSnapshot(int iter_no, double best_result) {
    if (!isSnapshotEnabled())
        return;
}

bool RandomSearch::isSnapshotEnabled() {
    return snapshot_frequency != std::nullopt;
}
