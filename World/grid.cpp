
#include <iostream>


#include "grid.h"
#include "physics.h"
#include "material.h"

using std::cout;
using std::endl;


WorldGrid::WorldGrid(int width, int height):
	_width(width),
	_height(height),
	mat_table(MaterialTable())
{
	_grid.resize(width);
	for (int i = 0; i < width; i++)
	{
		_grid[i].resize(height);
	}
}

void WorldGrid::insert_particle(int x, int y, MaterialID mat)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
	{
		cout << "invalid coordinate passed to insert_particle:" << x << " " << y << endl;
	}

	_grid[x][y] = Particle(mat_table[mat]);

}

void WorldGrid::update()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 1; j < _height; j++)
		{
			if (mat_table[_grid[i][j].material].phase() == Phase::solid && mat_table[_grid[i][j-1].material].phase() != Phase::solid)
			{
				insert_particle(i, j - 1, _grid[i][j].material);
				insert_particle(i, j, MaterialID::air);				
			}
		}
	}
}