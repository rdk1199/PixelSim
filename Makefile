build:

	g++ -c -std=c++17 main.cpp window_manager.cpp World/grid.cpp World/material.cpp Math/math.cpp
	g++ main.o window_manager.o grid.o material.o math.o -o pixel-sim -lsfml-graphics -lsfml-window -lsfml-system
	 ./pixel-sim
