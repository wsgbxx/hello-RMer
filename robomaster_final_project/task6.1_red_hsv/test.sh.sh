!/bin/bash


echo "正在编译程序..."
g++ -std=c++11 -o red_hsv_threshold red_hsv_threshold.cpp $(pkg-config --cflags --libs opencv4)
    chmod +x red_hsv_threshold
    ./red_hsv_threshold test_red_armor.jpg
    

