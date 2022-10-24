#include "random_search.hpp"
#include "swarm_search.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    std::vector<double>minX = {-40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40};
    std::vector<double>maxX = {40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40};
    //ustawienie seedu wyszukiwania losowego
    RandomSearch::setSeed();
    SearchResult searchResult1 = RandomSearch::search(minX, maxX, LOOPS_NUMBER);
    cout << "Wyszukiwanie losowe:\n";
    cout << "Najlepszy wynik: " << searchResult1.result << "\n";
    cout << "{";
    for(auto x : searchResult1.x)
        cout << x << ", ";
    cout << "}\n";
    cout << searchResult1.time << "[ns]\n";

    SwarmSearch swarmSearch;
    
    SearchResult searchResult2 = swarmSearch.search(minX, maxX, 10000, LOOPS_NUMBER / 11000); // dzielę przez 11000 aby wyrównać czasy obu metod
    cout << "Wyszukiwanie rojem cząstek:\n";
    cout << "Najlepszy wynik: " << searchResult2.result << "\n";
    cout << "{";
    for(auto x : searchResult2.x)
        cout << x << ", ";
    cout << "}\n";
    cout << searchResult2.time << "[ns]\n";
}