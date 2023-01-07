#include <algorithm>
#include <iostream>
#include <random>

#include "include/test_functions.hpp"

#define N 20

using Unifs = std::vector<std::uniform_real_distribution<double>>;

Unifs getUnifs();

int main() {
  std::mt19937 random_engine;

  int iterations = 100000;

  double best;

  auto unifs = getUnifs();

#pragma acc kernels
  for (int i = 0; i < iterations; ++i) {
    // generate point
    double point[N];
    for (int i = 0; i < N; ++i) {
      point[i] = unifs[i](random_engine);
    }

    // calculate sum of x squared
    double sum_of_x_squared;
    for (int i = 0; i < N; ++i) {
      sum_of_x_squared += point[i] * point[i];
    }

    // calculate cosinus part
    double cosinus_part = std::cos(point[0] / 1.0);
    for (int i = 2; i < N; ++i) {
      cosinus_part *= std::cos(point[i - 1] / i);
    }

    best = 1 / 40.0 * sum_of_x_squared + 1 - cosinus_part;
  }

  std::cout << "best: " << best << std::endl;
}

Unifs getUnifs() {
  Unifs unifs;
  for (size_t i = 0; i < N; ++i) {
    unifs.emplace_back(-40, 40);
  }
  return unifs;
}