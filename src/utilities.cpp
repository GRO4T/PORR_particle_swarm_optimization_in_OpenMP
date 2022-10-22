#include "utilities.hpp"

SearchResult createSearchResult(std::vector<double>x, double result)
{
    SearchResult searchResult;
    searchResult.x = x;
    searchResult.result = result;
    return searchResult;
}