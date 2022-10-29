#ifndef PLOTS_HPP
#define PLOTS_HPP

#include <functional>
#include <future>
#include <vector>

#include "utilities.hpp"

using TestFunction = std::function<double(std::vector<double>)>;

void display3DSurfacePlot(TestFunction func);
void plotClear();
void plotContourWithBestAndCurrentPoint(
    TestFunction objective_func,
    const Point& best_point,
    const Point& current_point,
    double min_x,
    double max_x,
    double animation_speed
);

#endif