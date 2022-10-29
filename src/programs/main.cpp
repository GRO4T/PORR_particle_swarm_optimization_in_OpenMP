#include "random_search.hpp"
#include "swarm_search.hpp"
#include <vector>
#include <iostream>
#include "test_functions.hpp"

using namespace std;

int main()
{
    std::vector<double> min_x = {-40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40};
    std::vector<double> max_x = {40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40};
    //ustawienie seedu wyszukiwania losowego
    RandomSearch::setSeed();

    SearchResult searchResult1 = RandomSearch::search(
        testFunc1,
        min_x,
        max_x,
        LOOPS_NUMBER
    );

    cout << "Wyszukiwanie losowe:\n";
    cout << "Najlepszy wynik: " << searchResult1.result << "\n";
    cout << "{";
    for(auto x : searchResult1.x)
        cout << x << ", ";
    cout << "}\n";
    cout << searchResult1.time << "[ns]\n";

    SwarmSearch swarmSearch;
    
    SearchResult searchResult2 = swarmSearch.search(min_x, max_x, 10000, LOOPS_NUMBER / 14000); // dzielę przez 14000 aby wyrównać czasy obu metod
    cout << "Wyszukiwanie rojem cząstek:\n";
    cout << "Najlepszy wynik: " << searchResult2.result << "\n";
    cout << "{";
    for(auto x : searchResult2.x)
        cout << x << ", ";
    cout << "}\n";
    cout << searchResult2.time << "[ns]\n";
}