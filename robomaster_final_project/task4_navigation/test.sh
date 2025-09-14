#!/bin/bash
echo "=== Testing Path Finder ==="
g++ -o path_finder path_finder_third.cpp
./path_finder map.txt 0 0 4 4
