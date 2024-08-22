
#pragma once


#include <vector>

#include "particle.h"


using std::vector; 

class WorldGrid
{
	//fixed properties
	int _width;
	int _height;
	float _scale; //how big (in meters) is a pixel?

	vector<vector<Particle>> grid;
	MaterialTable mat_table;

	//physics stuff
	void apply_gravity(int x, int y, float time_step); //updates velocity of particle at (x,y) based on gravitational acceleration
	pixel compute_desired_pos(int x, int y, float time_step, const Particle& particle);  //computes desired position based on particle's current velocity (assuming no collision)
	pixel handle_collisions(vector<pixel> path, float time_step, Particle& particle); //if particle collides with something at collision_px, then particle will be updated with new velocity based on various properties - returns final pixel location of particle
	void enforce_boundary(pixel final_pos, Particle& particle); //checks if particle has hit a boundary and modifies properties (i.e. velocity) accordingly

	pixel compute_final_pos(pixel curr_px, float time_step, Particle& particle); //computes new position of particle based on desired position (new_x/y) and old; also updates particle velocity to handle collision
	
	void move_particle(int x, int y, float time_step); //moves the particle at (x,y) based on its current velocity


public:


	WorldGrid(int width, int height, float scale = .1f);

	sf::Color get_px_col(int x, int y) const {return grid[x][y].color;} //returns the color of the particle at coordinate x,y
	void insert_particle(int x, int y, MaterialID mat); //replaces the particle at (x,y) with a particle made of mat

	

	void update(float time_step); //updates all particles in the grid

	

};