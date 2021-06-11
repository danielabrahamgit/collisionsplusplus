sim:
	g++ main.cpp Ball.cpp physics.cpp -std=c++11 -o sim -lfreeglut -lopengl32 -lstdc++
clean:
	rm sim.exe