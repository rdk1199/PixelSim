build:

	g++ -O2 -c -std=c++17 -Wno-narrowing main.cpp window_manager.cpp World/grid.cpp World/material.cpp Math/math.cpp Math/rand_util.cpp World/interaction.cpp
	g++ main.o window_manager.o grid.o material.o math.o rand_util.o interaction.o -o pixel-sim -lsfml-graphics -lsfml-window -lsfml-system
	 ./pixel-sim
