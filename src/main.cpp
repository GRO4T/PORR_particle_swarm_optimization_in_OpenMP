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
    SearchResult tmp = RandomSearch::search(minX, maxX, 0.1);
    cout << tmp.result << "\n";
}