#!/bin/bash
# Comiles and runs all .cpp files
g++ --std c++11 -fdiagnostics-color=always ./**.cpp -O3 -o l01.out
./l01.out
convert output.ppm output.jpeg