cmake_minimum_required(VERSION 3.16.3)

project(PORR)

add_compile_options(-fopenmp -std=c++11 -I/usr/include/python3.8 -lpython3.8 -Wall )

add_link_options(-fopenmp)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(PORR 
    src/main.cpp
    src/random_search.cpp
    src/test_functions.cpp
    src/utilities.cpp
    src/swarm_search.cpp
)
