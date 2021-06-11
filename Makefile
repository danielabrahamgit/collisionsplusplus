render:
	@g++ src/main.cpp src/Ball.cpp src/physics.cpp -std=c++11 -o sim -lfreeglut -lopengl32 -lstdc++
clean:
	@rm sim.exe