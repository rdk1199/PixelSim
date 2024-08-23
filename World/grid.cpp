
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

#include "grid.h"
#include "physics.h"
#include "material.h"
#include "../Math/rand_util.h"

using std::cout;
using std::endl;


WorldGrid::WorldGrid(int width, int height, float scale):
	_width(width),
	_height(height),
	_scale(scale),
	mat_table(MaterialTable())
{
	rand_init(time(0));
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

void WorldGrid::apply_gravity(int x, int y)
{
	grid[x][y].velocity += time_step * g;
}

pixel WorldGrid::compute_desired_pos(int x, int y, const Particle& particle)
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

void WorldGrid::enforce_boundary(pixel final_pos, Particle& particle)
{
//kill velocity in direction of boundaries when they impact -> this could become more interesting later
	if ((final_pos.x == 0 && particle.velocity.x < 0) || (final_pos.x == _width - 1 && particle.velocity.x >0))
	{
		particle.velocity.x = 0;
	}

	if ((final_pos.y == 0 && particle.velocity.y < 0) || (final_pos.y == _height - 1 && particle.velocity.y >0))
	{
		particle.velocity.y = 0;
	}

}



void WorldGrid::handle_ss_collision(pixel start_px, pixel coll_px) 
{
	Particle& particle = grid[start_px.x][start_px.y];
	Particle& collided_particle = grid[coll_px.x][coll_px.y];

	//adjust velocity of particle (just one for now)

	if (particle.material->slippery()) //randomly rotate velocity (deflect) and reduce magnitude by half
	{
		int angle = g_rand.rand_int(30, 45); //randomly choose a deflection angle

		if (!collided_particle.material->fixed())
		{
			collided_particle.velocity += 0.25f * particle.velocity; //impacted particle gets bumped as well
		}

		particle.velocity = .25f * (g_rand.flip() ? particle.velocity.rotated(angle) : particle.velocity.rotated(-angle)); //randomly pick a deflection direction


	}

	else //just kill velocity for now
	{
		particle.velocity = { 0,0 };
	}
}

void WorldGrid::handle_ll_collision(pixel start_px, pixel coll_px)
{

}

void WorldGrid::handle_sl_collision(pixel start_px, pixel coll_px)
{

}

void WorldGrid::handle_ls_collision(pixel start_px, pixel coll_px)
{

}


void WorldGrid::handle_collision(pixel start_px, pixel coll_px) //just passes input onto appropriate collision handler
{
	Particle start_p = grid[start_px.x][start_px.y];
	Particle coll_p = grid[coll_px.x][coll_px.y];

	if (start_p.material->phase() == Phase::solid && coll_p.material->phase() == Phase::solid)
	{
		handle_ss_collision(start_px, coll_px);
	}

	if (start_p.material->phase() == Phase::liquid && coll_p.material->phase() == Phase::solid)
	{
		handle_ls_collision(start_px, coll_px);
	}

	if (start_p.material->phase() == Phase::solid && coll_p.material->phase() == Phase::liquid)
	{
		handle_sl_collision(start_px, coll_px);
	}

	if (start_p.material->phase() == Phase::liquid && coll_p.material->phase() == Phase::liquid)
	{
		handle_ll_collision(start_px, coll_px);
	}

}


pixel WorldGrid::detect_collisions(vector<pixel> path, Particle& particle) //moves particle along path until it finds a collision (or doesn't) // path is assumed to be nonempty
{
	if (path.empty())
	{
		cout << " ERROR: handle_collisions passed empty path" << endl;
		exit(1);
	}

	pixel out = path.back(); //if no collision is found, out will be the last particle -> this covers case where path is size 1 as well, since next loop is skipped i n

	for (int i = 1; i < path.size(); i++) //look at all positions in order from start (not including start)
	{
		if (grid[path[i].x][path[i].y].material->phase() != Phase::gas) //found a collision
		{

			handle_collision(path[0], path[i]);
			out = path[i - 1]; //last known "good" position
			break;
		}
	}

	//
	enforce_boundary(out, particle);
	return out;
}



pixel WorldGrid::compute_final_pos(pixel curr_px, Particle& particle) //does collision math -> computes new velocity of particle and final position - could add bouncing later!
{
	pixel desired_px = compute_desired_pos(curr_px.x, curr_px.y, particle);

	//check every pixel along the "line" from current position to desired position until a collision occurs with another solid particle -> move there, kill velocity component in that direction

	vector<pixel> path = compute_line(curr_px, desired_px); 

	return detect_collisions(path, particle);
}

void WorldGrid::move_particle(int x, int y) //applies current velocity of particle over one timestep -does not yet consider collision
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
	{
		cout << "move_particle called on invalid coords: " << x << " " << y << endl;
	}

	Particle& particle = grid[x][y];
	pixel new_pos = compute_final_pos({ x, y }, particle);

	//move particle to new position
	particle.updated = true;
	grid[new_pos.x][new_pos.y] = particle; 
	


	if (new_pos.x != x || new_pos.y != y) //if particle moved, replace old position with air
	{
		insert_particle(x, y, MaterialID::air);
	}
}

void WorldGrid::update_particle(int x, int y)
{
	if (grid[x][y].material->phase() != Phase::gas && !grid[x][y].material->fixed() && !grid[x][y].updated)
	{
		apply_gravity(x, y);
		move_particle(x, y);
	}
}

void WorldGrid::update(float last_time_step)
{
	time_step = last_time_step;

	for (int i = 0; i < _width; i++)
	{
		for (int j = _height - 1; j >= 0; j--)
		{		
			update_particle(i, j);		
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