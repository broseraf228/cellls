#pragma once

#include "SFML/Graphics.hpp"
#include "../math/math.hpp"

class Cell_I {
public:
	virtual sf::Color get_color() const = 0;

};
struct substance {
	substance();
	substance(int protein, int herb, int mineral) ;
	int protein, herb, mineral;
};

class Substance_Cell : public Cell_I{
	substance content;
public:
	Substance_Cell(const substance&);

	sf::Color get_color() const ;
};

enum class ACTION {
	stay = 0,
	move,
	rotate_r,
	rotate_l
};
class Life_Cell : public Cell_I {
public:
	Life_Cell();

	Vect position{ 0 }; Matrix direction{};
	ACTION think();

	int energy;

	sf::Color get_color() const;
};