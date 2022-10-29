#include <cmath>
#include <thread>
#include <future>

#include "test_functions.hpp"
#include "plots.hpp"

int main()
{
    std::promise<void> exit_signal;
    std::future<void> exit_signal_future = exit_signal.get_future();
    std::thread plotter(display2DColormap, testFunc1, std::move(exit_signal_future));

    while (true) {
        std::string command;
        std::cout << "Press q to exit: ";
        std::cin >> command;

        if (command == "q") {
            std::cout << "Exiting...\n";
            exit_signal.set_value();
            break;
        }
    }

    std::cout << "Waiting for worker thread to finish...\n";
    plotter.join();
    std::cout << "Worker thread finished. Have a nice day :)\n";

    // WORKAROUND: plt::close does not close the window and whole programs hangs
    std::terminate();

    return 0;
}
