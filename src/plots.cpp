#include <chrono>

#include "plots.hpp"
#include "random_search.hpp"
#include "test_functions.hpp"

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void plotPoint(const Point& point, const std::string& color) {
    std::vector<double> x {point[0]};
    std::vector<double> y {point[1]};
    plt::plot(x, y, color);
}

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

void plotClear() {
    plt::clf();
}

void plotContourWithBestAndCurrentPoint(
    TestFunction objective_func,
    const Point& best_point,
    const Point& current_point,
    double min_x,
    double max_x,
    double animation_speed
) {
    // utworzenie współrzędnych do wygenerowania konturu
    std::vector<Point> contour_x, contour_y, contour_z;
    double contour_step = 0.25;
    for (double i = min_x; i <= max_x;  i += contour_step) {
        std::vector<double> x_row, y_row, z_row;
        for (double j = min_x; j <= max_x; j += contour_step) {
            x_row.push_back(i);
            y_row.push_back(j);
            double value = objective_func({i,j});
            z_row.push_back(value);
        }
        contour_x.push_back(x_row);
        contour_y.push_back(y_row);
        contour_z.push_back(z_row);
    }

    plt::contourf(contour_x, contour_y, contour_z);
    plotPoint(current_point, "bo");
    plotPoint(best_point, "ro");
    plt::pause(1.0 / animation_speed);
}

void plotContourWithQuiver(
    TestFunction objective_func,
    const Point& best,
    std::vector<double> x,
    std::vector<double> y,
    std::vector<double> u,
    std::vector<double> v,
    double min_x,
    double max_x,
    double animation_speed
) {
    // utworzenie współrzędnych do wygenerowania konturu
    std::vector<Point> contour_x, contour_y, contour_z;
    double contour_step = 0.25;
    for (double i = min_x; i <= max_x;  i += contour_step) {
        std::vector<double> x_row, y_row, z_row;
        for (double j = min_x; j <= max_x; j += contour_step) {
            x_row.push_back(i);
            y_row.push_back(j);
            double value = objective_func({i,j});
            z_row.push_back(value);
        }
        contour_x.push_back(x_row);
        contour_y.push_back(y_row);
        contour_z.push_back(z_row);
    }

    plt::contourf(contour_x, contour_y, contour_z);
    plt::quiver(x, y, u, v);
    plotPoint(best, "ro");
    plt::pause(1.0 / animation_speed);
}