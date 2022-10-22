#include "random_search.hpp"
#include <vector>

using namespace std;

int main()
{
    std::vector<double>minX = {-40, -40};
    std::vector<double>maxX = {40, 40};
    RandomSearch::search(minX, maxX, 0.1);
}