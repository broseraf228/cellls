#include "World.hpp"
#include "Cell.hpp"

Matrix r45 = Matrix::get_rotation(45);
Matrix l45 = Matrix::get_rotation(-45);

World::World(int sx, int sy){
	size = Vect(sx, sy);

	world.resize(sx);
	for (auto& item : world)
		item.resize(sy);
	map.resize(sx);
	for (auto& item : map)
		item.resize(sy);

	for(int x = 0; x < sx; x++)
		for (int y = 0; y < sy; y++)
		{
			if (((float)y - rand() % (y+1) * 2) / sy > 0.5)
				world[x][y] = new Substance_Cell(substance(rand() % 100, rand() % 100, rand() % 100));
			else
				world[x][y] = new Substance_Cell(substance(0, 0, 0));
		}

	int bx = 75, by = 10;
	
	bots.push_back(new Life_Cell());
	bots[0]->position = Vect(10, 10);
	bots[0]->energy = 100;
	

	update_using_map();
}

Vect World::get_size() {
	return size;
}
std::vector<std::vector<Cell_I*>>& World::get_map() {
	return map;
}
int World::inmx(int p) {
	if (p < 0)
		return size.x + p;
	if (p > size.x - 1)
		return p - size.x;
	return p;
}
int World::inmy(int p) {
	if (p < 0)
		return 0;
	if (p > size.y - 1)
		return size.y - 1;
	return p;
}
Vect World::inm(const Vect& v){
	return Vect(inmx(v.x), inmy(v.y));
}

void World::update_using_map() {
	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
		{
			map[x][y] = world[x][y];
		}
	for (auto item : bots)
		map[item->position.x][item->position.y] = item;
}

Cell_I* World::map_get_cell(int x, int y) {
	return map[x][y];
}
int World::map_get_light_power(int x, int y) {
	int res = round((size.y - y) / 10) - 1;
	if (res < 0)
		return 0;
	return res + 8;
}

void World::bot_move(Life_Cell* bot){
	Vect new_pos = inm(bot->position + bot->direction * Vect::get_default());
	if (map_get_cell(new_pos.x, new_pos.y)->get_solid())
		return;
	bot->position = new_pos;	
}
Vect World::bot_free_around_position(Life_Cell* bot) {
	Matrix dir = bot->direction;
	
	Vect pos = inm(bot->position + dir * Vect::get_default());
	for (int i = 0; i < 8; i++) {
		if (map_get_cell(pos.x, pos.y)->get_solid()) {
			dir = dir * r45;
			pos = inm(bot->position + dir * Vect::get_default());
			continue;
		}
		return pos;
	}
	return bot->position;
}


void World::update() {

	// bot actions
	Life_Cell* bot; int x, y; ACTION action;
	for (int i = 0; i < bots.size(); i++) {
		bot = bots[i];

		bot->age++;
		bot->energy -= bot->age * 0.5;

		action = bot->think();
		if (bot->energy > 150)
			action = ACTION::clone;
		if (bot->energy == 0)
			action = ACTION::die;
		
		Vect tmp_pos{0};
		switch (action)
		{
		case ACTION::stay:
			break;
		case ACTION::move:
			bot_move(bot);
			bot->energy -= 8;
			break;
		case ACTION::rotate_r:
			bot->direction = bot->direction * r45;
			bot->energy -= 1;
			break;
		case ACTION::rotate_l:
			bot->direction = bot->direction * l45;
			bot->energy -= 1;
			break;
		case ACTION::photosinthes:
			bot->energy += map_get_light_power(bot->position.x, bot->position.y);
			break;
		case ACTION::clone:
			tmp_pos = bot_free_around_position(bot);
			if (tmp_pos == bot->position)
			{
				goto DIE;
			}
			bot->energy -= 75;
			bots.push_back(bot->mitoze());
			bots[bots.size() - 1]->energy = 75;
			bots[bots.size() - 1]->position = tmp_pos;

			break;
		case ACTION::die:
		DIE:
			delete bots[i];
			bots.erase(bots.begin() + i);
			break;
		}

		update_using_map();
	}

	std::cout << "bots: " << bots.size() << std::endl;
}