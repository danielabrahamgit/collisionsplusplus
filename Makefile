sim:
	g++ main.cpp Ball.cpp physics.cpp -std=c++11 -o main -lfreeglut -lopengl32 -lstdc++
clean:
	rm main.exe