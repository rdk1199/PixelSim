
#pragma once


#include <vector>

#include "particle.h"


using std::vector; 

class WorldGrid
{
	int _width;
	int _height;
	vector<vector<Particle>> _grid;
	MaterialTable mat_table;


public:


	WorldGrid(int width, int height);

	sf::Color get_px_col(int x, int y) const {return _grid[x][y].color;} //returns the color of the particle at coordinate x,y
	void insert_particle(int x, int y, MaterialID mat);
	void update();

	

};