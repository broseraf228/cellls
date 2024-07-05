#include "World.hpp"
#include "Cell.hpp"

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
				world[x][y] = new Substance_Cell(substance(rand() % 255, rand() % 255, rand() % 255));
			else
				world[x][y] = new Substance_Cell(substance(0, 0, 0));
		}

	int bx = 75, by = 10;
	for (int i = 0; i < 100; i++) {
		bots.push_back(new Life_Cell());
		bots[i]->position = Vect(rand() % size.x, rand() % size.y);
	}

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

void World::bot_move(Life_Cell* bot){
	bot->position = bot->position + bot->direction * Vect::get_default();

	bot->position = inm(bot->position);
	
}

Matrix r45 = Matrix::get_rotation(45);
Matrix l45 = Matrix::get_rotation(-45);
void World::update() {
	Life_Cell* bot; int x, y; ACTION action;
	for (auto bot : bots) {
		action = bot->think();
		switch (action)
		{
		case ACTION::stay:
			break;
		case ACTION::move:
			bot_move(bot);
			break;
		case ACTION::rotate_r:
			bot->direction = bot->direction * r45;
			break;
		case ACTION::rotate_l:
			bot->direction = bot->direction * l45;
			break;
		default:
			break;
		}
	}

	update_using_map();

}