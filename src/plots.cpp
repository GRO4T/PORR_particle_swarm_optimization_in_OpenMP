#include "matplotlibcpp.h"

#include "plots.hpp"

namespace plt = matplotlibcpp;

void display3DSurfacePlot(std::function<double(std::vector<double>)> func) {
    std::vector<std::vector<double>> x, y, z;
    for (double i = -40; i <= 40;  i += 2) {
        std::vector<double> x_row, y_row, z_row;
        for (double j = -40; j <= 40; j += 2) {
            x_row.push_back(i);
            y_row.push_back(j);
            double value = func({i,j});
            z_row.push_back(value);
        }
        x.push_back(x_row);
        y.push_back(y_row);
        z.push_back(z_row);
    }

    plt::plot_surface(x, y, z);
    plt::show();
}