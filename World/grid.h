
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
	float time_step;

	vector<vector<Particle>> grid;
	MaterialTable mat_table;

	void update_particle(int x, int y);

	//physics stuff
	void apply_gravity(int x, int y); //updates velocity of particle at (x,y) based on gravitational acceleration
	pixel compute_desired_pos(int x, int y, const Particle& particle);  //computes desired position based on particle's current velocity (assuming no collision)
	pixel detect_collisions(vector<pixel> path, Particle& particle); //searches for particle to collide with along path and passes particles onto appropriate collision handler - returns final pixel location of particle
	
	
	//collision handlers
	
	void enforce_boundary(pixel final_pos, Particle& particle); //checks if particle has hit a boundary and modifies properties (i.e. velocity) accordingly

	void handle_collision(pixel start_px, pixel coll_px); //just passes input onto appropriate collision handler

	void handle_ss_collision(pixel start_px, pixel coll_px); //solid->solid collision
	void handle_ll_collision(pixel start_px, pixel coll_px); //liquid->liquid collision
	void handle_sl_collision(pixel start_px, pixel coll_px); //solid->liquid collision
	void handle_ls_collision(pixel start_px, pixel coll_px); //liquid->solid collision







	pixel compute_final_pos(pixel curr_px, Particle& particle); //computes new position of particle based on desired position (new_x/y) and old; also updates particle velocity to handle collision
	
	void move_particle(int x, int y); //moves the particle at (x,y) based on its current velocity


public:


	WorldGrid(int width, int height, float scale = .1f);

	sf::Color get_px_col(int x, int y) const {return grid[x][y].color;} //returns the color of the particle at coordinate x,y
	void insert_particle(int x, int y, MaterialID mat); //replaces the particle at (x,y) with a particle made of mat

	

	void update(float last_time_step); //updates all particles in the grid

	

};