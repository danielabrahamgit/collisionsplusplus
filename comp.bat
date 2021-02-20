@echo off 
g++ main.cpp Ball.cpp physics.cpp -o main -lfreeglut -lopengl32

if %1==-r (main.exe)