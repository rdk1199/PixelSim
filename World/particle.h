#pragma once

#include <SFML/Graphics/Color.hpp>

#include "material.h"
#include "../Math/math.h"

struct Particle 
{
	//intrinsic properties
	const Material* material; //holds pointer to something in material table
	sf::Color color;


	//dynamic properties
	vec2 velocity; // m/s 

	//bookkeeping
	bool updated = false; 

	Particle(const Material& mat) : material(&mat), color(mat.make_color()), velocity({ 0,0 }) {}
	
};

