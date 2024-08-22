#pragma once

#include <SFML/Graphics/Color.hpp>

#include "material.h"
#include "../Math/math.h"

struct Particle 
{
	//intrinsic properties
	MaterialID material;
	sf::Color color;


	//dynamic properties
	vec2 velocity; // m/s 

	//bookkeeping
	bool updated = false; 

	Particle(const Material& mat) : material(mat.id()), color(mat.make_color()), velocity({ 0,0 }) {}
	Particle() : material(MaterialID::air), color(sf::Color{ 0,0,0 }), velocity({ 0,0 }) {}


};