#pragma once

#include <vector>
#include "../math/math.hpp"


class Cell_I;
class Life_Cell;
class Substance_Cell;
class substance;

class World {
private:
	std::vector<std::vector<Substance_Cell*>> world;
	std::vector<Life_Cell*> bots;
	Vect size{0};

	std::vector<std::vector<Cell_I*>> map;
	int inmx(int p);
	int inmy(int p);
	

	void update_using_map();
public:
	World(int sx, int sy);

	void update();

	Cell_I* map_get_cell(int x, int y);
	Substance_Cell* map_get_world_cell(int x, int y);
	int map_get_light_power(int x, int y);
	void map_add_substance(const substance& sub, int x, int y);
	void bot_move(Life_Cell* bot, const Vect& dir);
	void bot_summon(Life_Cell* bot);

	Vect inm(const Vect&);
	Vect get_size();
	std::vector<std::vector<Cell_I*>>& get_map();
	const std::vector<Life_Cell*>& get_bots(); // ƒŒœ»—¿“‹
};