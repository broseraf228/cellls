#pragma once

#include "SFML/Graphics.hpp"
#include "../math/math.hpp"

class Cell_I {
public:
	virtual sf::Color get_color() const = 0;
	virtual bool get_solid() const = 0;

};
struct substance {
public:
	substance();
	substance(int protein, int organic, int mineral) ;
	int protein, organic, mineral;
	int size{100};

	int get_density() const;
};

class Substance_Cell : public Cell_I{
	substance content;
public:
	Substance_Cell(const substance&);

	sf::Color get_color() const ;
	bool get_solid() const ;
};

enum class ACTION {
	stay = 0,
	die,
	clone,
	move,
	rotate_r,
	rotate_l,

	photosinthes,
	organella_2,
	organella_3,

};
class Organella_I;
class Life_Cell : public Cell_I {
private:
	char genome[96];
	int current_command{0};

	Life_Cell(char* genome, const Matrix& rot);
public:
	Life_Cell();
	~Life_Cell();
	Life_Cell* mitoze();

	Vect position{ 0 }; Matrix direction{};
	ACTION think();

	int energy{ 0 };
	int age{ 0 };

	sf::Color get_color() const;
	bool get_solid() const;
};