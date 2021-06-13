UNAME := $(shell uname)

render:
ifeq ($(UNAME), Linux)
	@g++ src/main.cpp src/Ball.cpp src/physics.cpp -std=c++11 -o sim -lglut -lGL
else
	@g++ src/main.cpp src/Ball.cpp src/physics.cpp -std=c++11 -o sim -lfreeglut -lopengl32 -lstdc++
endif
clean:
	@rm sim.exe