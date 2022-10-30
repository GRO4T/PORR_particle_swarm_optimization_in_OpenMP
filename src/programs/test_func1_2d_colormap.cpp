#include <cmath>
#include <thread>
#include <future>

#include "test_functions.hpp"
#include "random_search.hpp"
#include "swarm_search.hpp"
#include "plots.hpp"

int main()
{
    auto random_search = []() {
        RandomSearch random_search(testFunc1, 2);
        random_search.plot(1000);
    };

    std::thread random_search_thread(random_search);

    random_search_thread.join();

    return 0;
}
