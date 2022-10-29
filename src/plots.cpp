#include "matplotlibcpp.h"
#include <chrono>

#include "plots.hpp"

namespace plt = matplotlibcpp;

void display3DSurfacePlot(TestFunction func) {
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

void display2DColormap(TestFunction func, std::future<void> exit_signal_future) {
    std::vector<std::vector<double>> x, y, z;
    for (double i = -40; i <= 40;  i += 0.25) {
        std::vector<double> x_row, y_row, z_row;
        for (double j = -40; j <= 40; j += 0.25) {
            x_row.push_back(i);
            y_row.push_back(j);
            double value = func({i,j});
            z_row.push_back(value);
        }
        x.push_back(x_row);
        y.push_back(y_row);
        z.push_back(z_row);
    }

    int i = 0;
    while (exit_signal_future.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) {
        plt::clf();
        std::vector<double> min_points_x = {i * 0.1};
        std::vector<double> min_points_y = {i * 0.1};

        plt::contourf(x, y, z);
        plt::plot(min_points_x, min_points_y, "ro");

        plt::pause(0.01);
        
        i++;
    }

    plt::close();
}