@echo off 
g++ main.cpp Ball.cpp physics.cpp -std=c++11 -o main -lfreeglut -lopengl32 -lstdc++

if %1==-r (main.exe)