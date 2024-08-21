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
	vec2 velocity;

	Particle(const Material& mat) : material(mat.id()), color(mat.make_color()) {}
	Particle() : material(MaterialID::air), color(sf::Color{ 0,0,0 }) {}


};