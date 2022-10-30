#include "random_search.hpp"
#include "swarm_search.hpp"
#include <vector>
#include <iostream>
#include "test_functions.hpp"
#include <string.h>

using namespace std;

int main(int argc, char** argv)
{
    int n = 20;
    int threads = 4;
    int iterations = 100000;

    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-n") == 0) {
            n = stoi(argv[i+1]);
        } else if (strcmp(argv[i], "--threads") == 0) {
            threads = stoi(argv[i+1]);
        } else if (strcmp(argv[i], "--iterations") == 0) {
            iterations = stoi(argv[i+1]);
        }
    }

    std::cout << "n: " << n << std::endl;
    std::cout << "threads: " << threads << std::endl;
    std::cout << "iterations: " << iterations << std::endl;

    RandomSearch random_search(testFunc1, n, threads);
    SearchResult searchResult1 = random_search.search(iterations);

    cout << "Wyszukiwanie losowe:\n";
    cout << "Najlepszy wynik: " << searchResult1.result << "\n";
    cout << "{";
    for(auto x : searchResult1.x)
        cout << x << ", ";
    cout << "}\n";
    cout << searchResult1.time << "[ns]\n";

    int particle_count = 100;
    SwarmSearch swarmSearch(testFunc1, n, particle_count, threads);
    SearchResult searchResult2 = swarmSearch.search(iterations);

    cout << "Wyszukiwanie rojem cząstek:\n";
    cout << "Najlepszy wynik: " << searchResult2.result << "\n";
    cout << "{";
    for(auto x : searchResult2.x)
        cout << x << ", ";
    cout << "}\n";
    cout << searchResult2.time << "[ns]\n";
}