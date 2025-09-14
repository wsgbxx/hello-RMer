#!/bin/bash

echo "正在编译程序..."
# 建议检查编译是否成功
if g++ -std=c++11 -o red_hsv_threshold red_hsv_threshold.cpp $(pkg-config --cflags --libs opencv4); then
    echo "编译成功，设置执行权限..."
    chmod +x red_hsv_threshold
    echo "运行程序..."
    ./red_hsv_threshold test_red_armor.jpg
else
    echo "编译失败，请检查错误信息"
    exit 1
fi