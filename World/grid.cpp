
#include <iostream>
#include <cmath>
#include <algorithm>

#include "grid.h"
#include "physics.h"
#include "material.h"

using std::cout;
using std::endl;


WorldGrid::WorldGrid(int width, int height, float scale):
	_width(width),
	_height(height),
	_scale(scale),
	mat_table(MaterialTable())
{
	grid.resize(width);
	for (int i = 0; i < width; i++)
	{
		grid[i].resize(height);
	}
}

void WorldGrid::insert_particle(int x, int y, MaterialID mat)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
	{
		cout << "invalid coordinate passed to insert_particle:" << x << " " << y << endl;
	}

	grid[x][y] = Particle(mat_table[mat]);

}

void WorldGrid::apply_gravity(int x, int y, float time_step)
{
	grid[x][y].velocity += time_step * g;
}

void WorldGrid::move_particle(int x, int y, float time_step) //applies current velocity of particle over one timestep -does not yet consider collision
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
	{
		cout << "move_particle called on invalid coords: " << x << " " << y << endl;
	}

	Particle& particle = grid[x][y];

	vec2 delta_p = (time_step * particle.velocity)/ _scale; //number of pixels to move

	//cout << delta_p << " " << y + delta_p.y << endl;

	int new_x = std::round(x + delta_p.x);
	int new_y = std::round(y + delta_p.y);

	new_x = std::clamp(new_x, 0, _width - 1); //clamp to boundaries
	new_y = std::clamp(new_y, 0, _height - 1);

	particle.updated = true;
	grid[new_x][new_y] = particle; //move particle to new position

	//cout << "velocity: " << particle.velocity << endl;
	cout << "new_x: " << new_x << " new_y: " << new_y << endl;

	if (new_x != x || new_y != y) //if particle moved, replace old position with air
	{
		insert_particle(x, y, MaterialID::air);
	}
}

void WorldGrid::update(float time_step)
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = _height - 1; j >= 0; j--)
		{
			if (mat_table[grid[i][j].material].phase() == Phase::solid && !grid[i][j].updated)
			{
				apply_gravity(i,j, time_step);
				move_particle(i,j, time_step);
			}
		}
	}

	for (int i = 0; i < _width; i++)
	{
		for (int j = _height - 1; j >= 0; j--)
		{
			grid[i][j].updated = false;
		}
	}
}