#ifndef PLOTS_HPP
#define PLOTS_HPP

#include <functional>

using TestFunction = std::function<double(std::vector<double>)>;

void display3DSurfacePlot(TestFunction func);
void display2DColormap(TestFunction func);

#endif