
#include "material.h"

Material::Material(MaterialID id, Phase phase, float density, sf::Color col_min, sf::Color col_max) :
	_id(id),
	_phase(phase),
	_density(density),
	_col_min(col_min),
	_col_max(col_max) {}

MaterialTable::MaterialTable() //put all material properties here
{
	Material air(MaterialID::air, Phase::gas, 1.293, { 0,0,0}, { 0,0,0});
	Material sand(MaterialID::sand, Phase::solid, 1500, { 225, 255, 225 }, { 225, 255, 225 });


	//these should be added in the SAME ORDER as in the enum
	mat_table.push_back(air);
	mat_table.push_back(sand);

}


