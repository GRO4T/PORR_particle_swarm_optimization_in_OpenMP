#include <cmath>
#include <thread>
#include <future>

#include "test_functions.hpp"
#include "random_search.hpp"
#include "plots.hpp"

int main()
{
    RandomSearch::setSeed();
    RandomSearch::plot(
        testFunc2,
        -40,
        40,
        1000
    );

    return 0;
}
