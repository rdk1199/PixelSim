
#include "material.h"

Material::Material(MaterialID id, Phase phase, float density, sf::Color col_min, sf::Color col_max, bool slippery, bool fixed) :
	_id(id),
	_phase(phase),
	_density(density),
	_col_min(col_min),
	_col_max(col_max),
	_slippery(slippery),
	_fixed(fixed)
{}

MaterialTable::MaterialTable() //put all material properties here
{
	Material air(MaterialID::air, Phase::gas, 1.293, { 1,0,0}, { 1,0,0});
	Material sand(MaterialID::sand, Phase::solid, 1500, { 255, 255, 225 }, { 255, 255, 225 }, true);
	Material rock(MaterialID::rock, Phase::solid, 1500, { 150, 150, 150 }, { 150, 150, 150 }, false, true);
	Material water(MaterialID::water, Phase::liquid, 1000, { 50,50, 255 }, { 50, 50, 255 }, true);


	//these should be added in the SAME ORDER as in the enum
	mat_table.push_back(air);
	mat_table.push_back(sand);
	mat_table.push_back(rock);
	mat_table.push_back(water);

}


