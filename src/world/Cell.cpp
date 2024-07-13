#include "Cell.hpp"
#include "World.hpp"
#include <map>

std::map<int, Matrix> rotations
{
	{0, Matrix::get_rotation(0)},
	{1, Matrix::get_rotation(45)},
	{2, Matrix::get_rotation(90)},
	{3, Matrix::get_rotation(135)},
	{4, Matrix::get_rotation(180)},
	{5, Matrix::get_rotation(-135)},
	{6, Matrix::get_rotation(-90)},
	{7, Matrix::get_rotation(-45)},
};

extern World* world;

substance::substance(int protein, int herb, int mineral) : 
	protein{ protein }, organic{ herb }, mineral{mineral} {
}
substance::substance() :
	protein{ 0 }, organic{ 0 }, mineral{ 0 } {
}
int substance::get_density() const{
	return protein + organic * 0.5 + mineral;
}


Substance_Cell::Substance_Cell(const substance& sub) {
	content = sub;
	update_color();
}
CELLS Substance_Cell::type(){
	return CELLS::sub;
}
substance& Substance_Cell::get_substance(){
	return content;
}
const sf::Color& Substance_Cell::get_color() const {
	return col;
}
bool Substance_Cell::get_solid() const {
	if(content.get_density() >= 25)
		return true;
	return false;
}
int Substance_Cell::eat_energy(int power)
{
	int res = 0;
	if (content.organic > power)
		res = power;
	else
		res = content.organic;

	content.organic -= res;

	return res;
}
void Substance_Cell::add(const substance& sub)
{
	content.protein = content.protein + sub.protein > 100 ? 100 : content.protein + sub.protein;
	content.organic = content.organic + sub.organic > 100 ? 100 : content.organic + sub.organic;
	content.mineral = content.mineral + sub.mineral > 100 ? 100 : content.mineral + sub.mineral;
	update_color();
}
void Substance_Cell::update_color(){
	float m = 255 / content.size;
	col = sf::Color(content.protein * m, content.organic * m, content.mineral * m, 125);
}

Life_Cell::Life_Cell(char* igenome, const Matrix& rot) {
	direction = rot;
	int R = 0, G = 0, B = 0;
	for (int i = 0; i < 64; i++) {
		genome[i] = igenome[i];
		if (genome[i] == 0)
			G++;
		if (genome[i] >= 11 && genome[i] <= 13)
			R++;
	}
	if (rand() % 3 == 0) {
		genome[rand() % 64] = rand() % 64;
	}
	if (rand() % 3 == 0) {
		genome[rand() % 64] = rand() % 64;
	}
	if (rand() % 3 == 0) {
		genome[rand() % 64] = rand() % 64;
	}

	int summ = R + G + B;
	float revSunn = 1 / summ;
	col = sf::Color(R + revSunn * 96 + 100, G + revSunn * 96 + 100, B + revSunn * 96 + 100);
}
CELLS Life_Cell::type() {
	return CELLS::bot;
}
Life_Cell::Life_Cell() {
	direction = Matrix::get_default() * Matrix::get_rotation(90);
	for (int i = 0; i < 64; i++) {
		if (i % 2 == 0)
			genome[i] = 0;
		else
			genome[i] = 13;
	}
}
Life_Cell::~Life_Cell() {
}
const sf::Color& Life_Cell::get_color() const {
	return col;
}
bool Life_Cell::get_solid() const {
	return true;
}

int Life_Cell::current_command() {
	return genome[command_counter % 96];
}
int Life_Cell::next_command(int s) {
	command_counter = (command_counter + s) % 96;
	return current_command();
}
void Life_Cell::step() {
	
	if (energy > cloning_energy) {
		Matrix dir = direction; Vect pos{0};
		for (int i = 0; i < 5; i++) {
			dir = rotations[1] * dir;
			pos = world->inm(position + dir * Vect::get_default());
			if (world->map_get_cell(pos.x, pos.y)->get_solid()) //если €чейка тверда€
			{
				if (i == 4) {
					energy = -200 - energy;
					return;
				}
				continue;
			}
			//иначе
			Life_Cell* soon = new Life_Cell(genome, direction * rotations[rand() % 4]);
			soon->position = pos;
			soon->energy = soon_energy;
			energy -= cloning_coast;
			world->bot_summon(soon);
			return;
		}
	}

COMM:
	int command = current_command();

	// photosynthes
	if (command == 0) {
		next_command();
		energy += world->map_get_light_power(position.x, position.y);
		return;
	} 
	// move
	if (command >= 1 && command <= 2) {
		next_command();
		switch (command) {
		case 1:
			world->bot_move(this, Vect::get_default());
			energy -= 8;
			return;
		case 2:
			world->bot_move(this, Vect::get_default() * -1);
			energy -= 8;
			return;
		}
	}
	// rotate
	if (command >= 3 && command <= 10) {
		Vect pos = world->inm(direction * rotations[command - 3] * Vect::get_default());
		if (world->map_get_cell(pos.x, pos.y)->type() == CELLS::sub)
			next_command(1);
		else
			next_command(2);
		direction = direction * rotations[command - 3];
		energy -= 1;
		goto COMM;
	}
	// eat ( herb from world )
	if (command >= 11 && command <= 13) {
		int m;
		switch (command)
		{
		case 11:
			m == 1;
			break;
		case 12:
			m == 0;
			break;
		case 13:
			m == 7;
			break;
		}
		Matrix dir = direction * rotations[m];
		Vect pos = world->inm(position + dir * Vect::get_default());
		int ener = world->map_get_cell(pos.x , pos.y)->eat_energy(10) * 0.8;
		if (ener != 0)
			next_command(1);
		else
			next_command(2);
		energy += ener;
		return;
	}
	if (command == 14) {
		int ener = world->map_get_world_cell(position.x, position.y)->eat_energy(10) * 0.8;
		if (ener != 0)
			next_command(1);
		else
			next_command(2);
		energy += ener;
		return;
	}
	else
		next_command();
}

int Life_Cell::eat_energy(int power)
{
	int res = 0;
	if (energy > power) {
		res = power;
	}
	else {
		res = energy;
		energy = -100;
	}

	return res;
}