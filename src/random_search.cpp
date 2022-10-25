#include "random_search.hpp"

#include "test_functions.hpp"

#include <float.h>
#include <cassert>
#include <chrono>
#include <omp.h>

thread_local std::mt19937 RandomSearch::random_engine;

void RandomSearch::setSeed(int seed /*= time(NULL)*/)
{
    random_engine = std::mt19937(seed);
}

SearchResult RandomSearch::search(std::vector<double>&minX, std::vector<double>&maxX, size_t iterations)
{
    omp_set_num_threads(8);
    assert((minX.size() == maxX.size()) && "Different dimensions in range of domain");
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    SearchResult bestResult;
    bestResult.result = DBL_MAX;
    // int loppsWithoutEpsilon = 0;
    size_t i_number = 0;

    // ustawienie zakresu losowania
    std::vector<std::uniform_real_distribution<double>> unifs;
    for(unsigned int i = 0; i < minX.size(); ++i)
    {
        unifs.push_back(std::uniform_real_distribution<double>(minX[i], maxX[i]));
    }

    #ifdef OPENMP_ENABLED
        #pragma omp parallel for shared(bestResult, unifs) num_threads(OMP_NUM_THREADS)
    #endif
    for(int i = 0; i < iterations; ++i)
    {
        std::vector<double>x;
        for(auto unif : unifs)
        {
            x.push_back(unif(random_engine));
        }
        double result = testFunc1(x);
        #ifdef OPENMP_ENABLED
        #pragma omp critical
        {
        #endif
            if(result < bestResult.result)
            {
                bestResult = createSearchResult(x, result);
            }
        #ifdef OPENMP_ENABLED
        }
        #endif
    }
    bestResult.time = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - begin).count();
    return bestResult;
}



