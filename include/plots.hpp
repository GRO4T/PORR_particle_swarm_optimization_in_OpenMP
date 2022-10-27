#ifndef PLOTS_HPP
#define PLOTS_HPP

#include <functional>

void display3DSurfacePlot(std::function<double(std::vector<double>)> func);

#endif