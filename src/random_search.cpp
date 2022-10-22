#include "random_search.hpp"

#include "test_functions.hpp"

#include <float.h>
#include <cassert>

std::default_random_engine RandomSearch::random_engine;

void RandomSearch::setSeed(int seed /*= time(NULL)*/)
{
    random_engine = std::default_random_engine(seed);
}

SearchResult RandomSearch::search(std::vector<double>minX, std::vector<double>maxX, double epsilon, int iterations /* = -1*/)
{
    assert((minX.size() == maxX.size()) && "Different dimensions in range of domain");
    SearchResult bestResult;
    bestResult.result = DBL_MAX;
    int loppsWithoutEpsilon = 0;
    int i_number = 0;
    double prevValue = DBL_MAX; 

    // ustawienie zakresu losowania
    std::vector<std::uniform_real_distribution<double>> unifs;
    for(unsigned int i = 0; i < minX.size(); ++i)
    {
        unifs.push_back(std::uniform_real_distribution<double>(minX[i], maxX[i]));
    }


    while(LOOPS_WITHOUT_EPSILON_TO_STOP > loppsWithoutEpsilon && (iterations == -1 || i_number < iterations))
    {
        i_number++;
        loppsWithoutEpsilon++;

        std::vector<double>x;
        for(auto unif : unifs)
        {
            x.push_back(unif(random_engine));
        }
        double result = testFunc1(x);
        if(result < bestResult.result)
        {
            createSearchResult(x, result);
        }
        if(prevValue - epsilon >= result)
        {
            loppsWithoutEpsilon = 0;
        }
        prevValue = result;
    }
}



