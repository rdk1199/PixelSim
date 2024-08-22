
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
	grid.resize(width, vector<Particle>(height, Particle(mat_table[MaterialID::air])));
	
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

pixel WorldGrid::compute_desired_pos(int x, int y, float time_step, const Particle& particle)
{
	vec2 delta_p = (time_step * particle.velocity) / _scale; //number of pixels to move

	//cout << delta_p << " " << y + delta_p.y << endl;

	int new_x = std::round(x + delta_p.x);
	int new_y = std::round(y + delta_p.y);

	new_x = std::clamp(new_x, 0, _width - 1); //clamp to boundaries
	new_y = std::clamp(new_y, 0, _height - 1);

	new_x = std::clamp(new_x, 0, _width - 1); //clamp to boundaries
	new_y = std::clamp(new_y, 0, _height - 1);

	return { new_x, new_y };
}

pixel WorldGrid::compute_collisions(pixel curr_px, float time_step, Particle& particle) //does collision math -> computes new velocity of particle and final position - could add bouncing later!
{
	pixel desired_px = compute_desired_pos(curr_px.x, curr_px.y, time_step, particle);

	//check every pixel along the "line" from current position to desired position until a collision occurs with another solid particle -> move there, kill velocity component in that direction

	vector<pixel> line = compute_line(curr_px, desired_px); 

	if (line.size() == 1) //current and desired are the same -> don't do anything
	{
		return curr_px;
	}

	for (int i = 1; i < line.size(); i++) //look at all positions in order from start (not including start)
	{
		if (grid[line[i].x][line[i].y].material->phase() == Phase::solid) //found a collision
		{
			return line[i - 1]; //last known "good" position
		}
	}

	//no collision found - don't modify velocity and return desired position
	return desired_px;
}

void WorldGrid::move_particle(int x, int y, float time_step) //applies current velocity of particle over one timestep -does not yet consider collision
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
	{
		cout << "move_particle called on invalid coords: " << x << " " << y << endl;
	}

	Particle& particle = grid[x][y];
	pixel new_pos = compute_collisions({ x, y }, time_step, particle);

	//move particle to new position
	particle.updated = true;
	grid[new_pos.x][new_pos.y] = particle; 
	


	if (new_pos.x != x || new_pos.y != y) //if particle moved, replace old position with air
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
			if (grid[i][j].material->phase() == Phase::solid && !grid[i][j].updated)
			{
				apply_gravity(i,j, time_step);
				move_particle(i,j, time_step);
			}
		}
	}

	for (int i = 0; i < _width; i++) //reset grid for next update 
	{
		for (int j = _height - 1; j >= 0; j--)
		{
			grid[i][j].updated = false;
		}
	}
}