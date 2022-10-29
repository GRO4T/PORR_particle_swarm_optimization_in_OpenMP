cmake_minimum_required(VERSION 3.16.3)

project(PORR)

set(CMAKE_CXX_STANDARD 11)

####################################
# Main executable
####################################

add_executable(PORR 
    src/programs/main.cpp
    src/plots.cpp
    src/random_search.cpp
    src/test_functions.cpp
    src/utilities.cpp
    src/swarm_search.cpp
)

target_compile_options(PORR PRIVATE -fopenmp -Wall)

target_link_options(PORR PRIVATE -fopenmp)

target_include_directories(PORR PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/python3.10
)

target_link_libraries(PORR PRIVATE python3.10)

####################################
# Plots
####################################

add_executable(test_func1_3d_plot
    src/programs/test_func1_3d_plot.cpp
    src/test_functions.cpp
    src/plots.cpp
)
target_link_libraries(test_func1_3d_plot PRIVATE python3.10)
target_include_directories(test_func1_3d_plot PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/python3.10
)

add_executable(test_func2_3d_plot
    src/programs/test_func2_3d_plot.cpp
    src/test_functions.cpp
    src/plots.cpp
)
target_link_libraries(test_func2_3d_plot PRIVATE python3.10)
target_include_directories(test_func2_3d_plot PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/python3.10
)

add_executable(test_func1_2d_colormap
    src/programs/test_func1_2d_colormap.cpp
    src/test_functions.cpp
    src/plots.cpp
    src/random_search.cpp
)
target_compile_options(test_func1_2d_colormap PRIVATE -fopenmp -Wall)

target_link_options(test_func1_2d_colormap PRIVATE -fopenmp)
target_link_libraries(test_func1_2d_colormap PRIVATE python3.10)
target_include_directories(test_func1_2d_colormap PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/python3.10
)
