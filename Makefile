build:

	g++ -c -std=c++17 main.cpp window_manager.cpp World/grid.cpp World/material.cpp
	g++ main.o window_manager.o grid.o material.o -o pixel-sim -lsfml-graphics -lsfml-window -lsfml-system
	 ./pixel-sim
