#include "random_search.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    std::vector<double>minX = {-40, -40};
    std::vector<double>maxX = {40, 40};
    //ustawienie seedu wyszukiwania losowego
    RandomSearch::setSeed();
    SearchResult tmp = RandomSearch::search(minX, maxX, LOOPS_NUMBER);
    cout << tmp.result << "\n";
    cout << "{";
    for(auto x : tmp.x)
        cout << x << ", ";
    cout << "}\n";
    cout << tmp.time << "[ns]\n";
}