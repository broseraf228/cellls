#pragma once

#include <vector>
#include "../math/math.hpp"

class Cell_I;
class Life_Cell;
class Substance_Cell;

class World {
private:
	std::vector<std::vector<Substance_Cell*>> world;
	std::vector<Life_Cell*> bots;
	Vect size{0};

	std::vector<std::vector<Cell_I*>> map;
	int inmx(int p);
	int inmy(int p);
	Vect inm(const Vect&);

	void update_using_map();
	// ONLY FOR MOVEING, NOT _ENERGY!!!!!!!!
	void bot_move(Life_Cell* bot);
	// return position on free place aroun bot, else return bot position
	Vect bot_free_around_position(Life_Cell* bot);
public:
	World(int sx, int sy);

	void update();

	Cell_I* map_get_cell(int x, int y);
	int map_get_light_power(int x, int y);

	Vect get_size();
	std::vector<std::vector<Cell_I*>>& get_map();
};