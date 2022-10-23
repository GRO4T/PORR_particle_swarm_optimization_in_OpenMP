#!/bin/bash
g++ $1 src/test_functions.cpp -std=c++11 -I/usr/include/python3.10 -lpython3.10
