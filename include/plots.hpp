#ifndef PLOTS_HPP
#define PLOTS_HPP

#include <functional>
#include <future>

using TestFunction = std::function<double(std::vector<double>)>;

void display3DSurfacePlot(TestFunction func);
void display2DColormap(TestFunction func, std::future<void> exit_signal_future);

#endif