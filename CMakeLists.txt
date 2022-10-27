cmake_minimum_required(VERSION 3.16.3)

project(PORR)

set(CMAKE_CXX_STANDARD 11)

####################################
# Main executable
####################################

add_executable(PORR 
    src/main.cpp
    src/random_search.cpp
    src/test_functions.cpp
    src/utilities.cpp
    src/swarm_search.cpp
)

target_compile_options(PORR PRIVATE -fopenmp -Wall)

target_link_options(PORR PRIVATE -fopenmp)

target_include_directories(PORR PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

####################################
# Plots
####################################

add_executable(plot_test_func1
    src/plot_test_func1.cpp
    src/test_functions.cpp
)

add_executable(plot_test_func2
    src/plot_test_func2.cpp
    src/test_functions.cpp
)

target_link_libraries(plot_test_func1 PRIVATE python3.10)
target_link_libraries(plot_test_func2 PRIVATE python3.10)
target_include_directories(plot_test_func1 PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/python3.10
)
target_include_directories(plot_test_func2 PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/python3.10
)
