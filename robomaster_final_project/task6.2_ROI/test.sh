#!/bin/bash
echo "编译程序..."
g++ -o detect_circle detect_circle.cpp `pkg-config --cflags --libs opencv4`
./detect_circle test_rune.png


