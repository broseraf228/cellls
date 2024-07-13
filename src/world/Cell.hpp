#pragma once

#include "SFML/Graphics.hpp"
#include "../math/math.hpp"

struct substance {
public:
	substance();
	substance(int protein, int organic, int mineral);
	int protein, organic, mineral;
	int size{ 100 };

	int get_density() const;
};

enum class CELLS {
	sub,
	bot
};

class Cell_I {
public:
	virtual const sf::Color& get_color() const = 0;
	virtual bool get_solid() const = 0;
	virtual int eat_energy(int power) = 0;

	virtual CELLS  type() = 0;

};

class Substance_Cell : public Cell_I{
	substance content;

	sf::Color col;
public:
	Substance_Cell(const substance&);
	CELLS  type();

	const sf::Color& get_color() const ;
	bool get_solid() const ;
	int eat_energy(int power) ;

	void add(const substance&);
	void update_color();

	substance& get_substance();
};


class Life_Cell : public Cell_I {
private:
	sf::Color col;
public:
	Life_Cell();
	CELLS  type();
	// mutate genome
	Life_Cell(char* genome, const Matrix& rot);
	~Life_Cell();

	Vect position{ 0 }; Matrix direction{};
	void step();

	int energy{ 0 };
	int age{ 0 };
	int minerale{ 0 };
	char genome[64];
	int command_counter{ 0 };
	inline int current_command();
	int next_command(int s = 1);

	const sf::Color& get_color() const;
	bool get_solid() const;

	int eat_energy(int power);

	static const int cloning_energy = 300;
	static const int cloning_coast = 200;
	static const int soon_energy = 50;
};