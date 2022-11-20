#include "random_search.hpp"
#include "swarm_search.hpp"
#include <iostream>
#include "test_functions.hpp"
#include <cstring>

using namespace std;

void print_as_json(const SearchResult& search_result);
void print_help();

int main(int argc, char** argv)
{
    int n = 20;
    int threads = 4;
    int iterations = 100000;
    int seconds = 5;
    int objective_func_id = 1;
    std::string search_algorithm = "random";
    std::string end_condition = "iteration";

    for (int i = 0; i < argc; ++i) {
        if ((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--dimension") == 0)) {
            n = stoi(argv[i+1]);
        } else if ((strcmp(argv[i], "-t") == 0) || (strcmp(argv[i], "--threads") == 0)) {
            threads = stoi(argv[i+1]);
        } else if ((strcmp(argv[i], "-i") == 0) || (strcmp(argv[i], "--iter") == 0)) {
            iterations = stoi(argv[i+1]);
            end_condition = "iteration";
        } else if ((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--search") == 0)) {
            search_algorithm = argv[i+1];
        } else if ((strcmp(argv[i], "-f") == 0) || (strcmp(argv[i], "--obj_func") == 0)) {
            objective_func_id = stoi(argv[i+1]);
        } else if ((strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "--time") == 0)) {
            seconds = stoi(argv[i+1]);
            end_condition = "time";
        } else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
            print_help();
            exit(0);
        }
    }

    std::cout << "---------------------------------------" << std::endl;
    std::cout << "n: " << n << std::endl;
    std::cout << "threads: " << threads << std::endl;
    std::cout << "iterations: " << iterations << std::endl;
    std::cout << "search_algorithm: " << search_algorithm << std::endl;
    std::cout << "objective_func_id: " << objective_func_id << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    SearchResult search_result;
    ObjectiveFunc objective_func = objective_func_id == 1 ? testFunc1 : testFunc2;
    double bound_x = objective_func_id == 1 ? 40 : 30;

    if (search_algorithm == "random") {
        if (end_condition == "iteration") {
            RandomSearch random_search(objective_func, n, threads, -bound_x, bound_x);
            search_result = random_search.search(iterations);
        } else if (end_condition == "time") {
            RandomSearch random_search(objective_func, n, threads, -bound_x, bound_x);
            search_result = random_search.searchForXSeconds(seconds);
        }
    } else if (search_algorithm == "swarm") {
        int particle_count = 100;
        SwarmSearch swarmSearch(objective_func, n, particle_count, threads, -bound_x, bound_x);
        search_result = swarmSearch.search(iterations);
    }

    std::cout << "Search: " << search_algorithm << std::endl;
    std::cout << "Result:\n";
    print_as_json(search_result);
}

void print_as_json(const SearchResult& search_result) {
    cout << "{\n";
    std::cout << "\t\"value\": " << search_result.result << "\n";
    std::cout << "\t\"position\": [";
    for(auto x : search_result.x)
        cout << x << ", ";
    std::cout << "]\n";

    std::cout << "\t\"exec_time_in_nanos\": " << search_result.time << "\n";
    std::cout << "\t\"exec_time\": " << (double) search_result.time / 1000000000.0 << "\n";

    std::cout << "}\n";
}

void print_help() {
    std::cout << "usage: runner [-h | --help] [-n | --dimension] DIMENSION [-t | --threads] THREADS\n"
              << "[-i | --iterations] ITERATIONS [-s | --search] SEARCH_ALGORITHM [-f | --obj_func] OBJ_FUNC\n"
              << "[-m | --time] TIME\n"
              << "\tdimension - number of dimensions of test function\n"
              << "\tthreads - number of threads\n"
              << "\titer - finish after X iterations\n"
              << "\tsearch - search algorithm (random or swarm)\n"
              << "\tobj_func - id of test function (1 or 2)\n"
              << "\ttime - finish after X seconds\n"
              ;
}