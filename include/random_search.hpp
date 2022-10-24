#ifndef RANDOM_SEARCH
#define RANDOM_SEARCH

#include <time.h>
#include <random>

#include "utilities.hpp"

class RandomSearch
{
public:
    static void setSeed(int seed = time(NULL));
    static SearchResult search(std::vector<double>&minX, std::vector<double>&maxX, size_t iterations);
    static std::default_random_engine random_engine;
private:
    

};


#endif