#include "matplotlibcpp.h"

#include <cmath>

#include "test_functions.hpp"



namespace plt = matplotlibcpp;

int main()
{
    std::vector<std::vector<double>> x, y, z;
    for (double i = -40; i <= 40;  i += 2) {
        std::vector<double> x_row, y_row, z_row;
        for (double j = -40; j <= 40; j += 2) {
            x_row.push_back(i);
            y_row.push_back(j);
            z_row.push_back(testFunc2({i,j}));
        }
        x.push_back(x_row);
        y.push_back(y_row);
        z.push_back(z_row);
    }

    plt::plot_surface(x, y, z);
    plt::show();
}
