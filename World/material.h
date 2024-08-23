
#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics/Color.hpp>

using std::vector;
using std::cout;
using std::endl;

enum class Phase {solid, liquid, gas};
enum class MaterialID { air, sand, rock, water }; //enum value should = index in material table

class Material
{
	MaterialID _id;
	
	//material properties
	Phase _phase;
	float _density;
	bool _slippery = false; //will this material slide over itself?
	bool _fixed = false; //fixed materials will not move at all

	//color properties - color values fall in these ranges 
	sf::Color _col_min;
	sf::Color _col_max;

public: 

	Material(MaterialID id, Phase phase, float density, sf::Color col_min, sf::Color col_max, bool slippery = false, bool fixed = false);

	MaterialID id() const { return _id; }
	Phase phase() const { return _phase; }
	bool slippery() const { return _slippery; }
	bool fixed() const { return _fixed; }
	sf::Color make_color() const { return _col_min; }

};

class MaterialTable
{
	 vector<Material> mat_table;

public:

	MaterialTable();

	 const Material& operator[](const MaterialID& index) const 
	 {
		 int i = static_cast<int>(index);

		 if (i < 0 || i >= mat_table.size())
		 {
			 cout << "material table out of bounds access" << endl;
			 exit(0);
		 }

		 return mat_table[i]; 
	 }

};

