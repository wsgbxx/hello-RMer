#!/bin/bash    
echo "=== Testing Command Analyzer ==="
g++ -o command_analyzer command_analyzer.cpp
./command_analyzer commands.log
#cd ~/Desktop/robomaster_final_project/task3_tactical
#ls -l test.sh
#chmod +x test.sh
#./test.sh
