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
const std::vector<Life_Cell*>& World::get_bots() {
	return bots;
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
Substance_Cell* World::map_get_world_cell(int x, int y) {
	return world[x][y];
}
int World::map_get_light_power(int x, int y) {
	int res = round((size.y - y) / 10) - 4;
	if (res < 0)
		return 0;
	return res + 8;
}
void World::map_add_substance(const substance& sub, int x, int y)
{
	world[x][y]->add(sub);
}

void World::bot_move(Life_Cell* bot, const Vect& dir){
	Vect new_pos = inm(bot->position + bot->direction * dir);
	if (map_get_cell(new_pos.x, new_pos.y)->get_solid())
		return;
	map[bot->position.x][bot->position.y] = world[bot->position.x][bot->position.y];
	bot->position = new_pos;	
	map[bot->position.x][bot->position.y] = bot;
}
void World::bot_summon(Life_Cell* bot) {
	bots.push_back(bot);
	map[bot->position.x][bot->position.y] = bot;
}

static int oo = 0;
void World::update() {

	// bot actions
	Life_Cell* bot; int x, y;
	for (int i = 0; i < bots.size(); i++) {
		bot = bots[i];

		bot->age++;
		bot->energy -= 1 + bot->age * 0.005;

		if (bot->energy <= 100) {
			world[bot->position.x][bot->position.y]->add(substance(0, 1, 0));
		}
		if (bot->energy <= 0) {
			delete bots[i];
			bots.erase(bots.begin() + i);
			update_using_map();
			continue;
		}

		bot->step();
	}

	// update world
	if (oo++ % 5 == 0) 
	{
		for (int x = 0; x < size.x; x++) {
			for (int y = size.y - 1; y > 1; y--) {
				if (world[x][y - 1]->get_substance().organic >= 25 && world[x][y]->get_substance().organic < 100 && map[x][y]->type() == CELLS::sub)
				{
					world[x][y]->get_substance().organic += 25;
					world[x][y - 1]->get_substance().organic -= 25;
				}
			}
		}
	}
	for (int x = 0; x < size.x; x++) {
		for (int y = 0; y < size.y; y++) {
			if(world[x][y]->get_substance().organic > 50 && rand() % 3 == 0)
				world[x][y]->get_substance().organic--;
		}
	}
	update_using_map();

	// update world colors;
	for (int x = 0; x < size.x; x++) {
		for (int y = 0; y < size.y; y++) {
			world[x][y]->update_color();
		}
	}
}