#include "Cell.hpp"
#include "Organella.hpp"

substance::substance(int protein, int herb, int mineral) : 
	protein{ protein }, organic{ herb }, mineral{mineral} {
}
substance::substance() :
	protein{ 0 }, organic{ 0 }, mineral{ 0 } {
}
int substance::get_density() const{
	return (protein * 0.7 + organic * 0.3 + mineral) / size;
}

Substance_Cell::Substance_Cell(const substance& sub) {
	content = sub;
}
sf::Color Substance_Cell::get_color() const {
	float m = 255 / content.size;
	return sf::Color(content.protein * m, content.organic * m, content.mineral * m, 125);
}
bool Substance_Cell::get_solid() const {
	if(content.get_density() > 1)
		return true;
	return false;
}

Life_Cell::Life_Cell(char* igenome, const Matrix& rot) {
	direction = rot;
	for (int i = 0; i < 96; i++)
		genome[i] = igenome[i];
}
Life_Cell::Life_Cell() {
	direction = Matrix::get_default() * Matrix::get_rotation(90);
	for (int i = 0; i < 96; i++)
		genome[i] = 65;
}
Life_Cell::~Life_Cell() {
}
Life_Cell* Life_Cell::mitoze() {
	char newGenome[96];
	for (int i = 0; i < 96; i++) {
		newGenome[i] = genome[i];
		if (rand() % 2 == 0)
			genome[i] += rand() % 3 - 1;
	}
	Life_Cell* soon = new Life_Cell(newGenome, direction);
	return soon;
}
sf::Color Life_Cell::get_color() const {
	return sf::Color(255, 100, 0, 255);
}
bool Life_Cell::get_solid() const {
	return true;
}
ACTION Life_Cell::think() {
	switch (genome[current_command])
	{
	case 65:
		current_command = (current_command + 1) % 96;
		return ACTION::photosinthes;
	case 66:
		current_command = (current_command + 1) % 96;
		return ACTION::move;
	case 67:
		current_command = (current_command + 1) % 96;
		return ACTION::rotate_l;
	case 68:
		current_command = (current_command + 1) % 96;
		return ACTION::rotate_r;
	case 69:
		current_command = (current_command + 1) % 96;
		return ACTION::photosinthes;
	default:
		current_command = (current_command + 1) % 96;
		break;
	}
}