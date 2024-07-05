#include "Cell.hpp"

substance::substance(int protein, int herb, int mineral) : 
	protein{ protein }, herb{ herb }, mineral{mineral} {
}
substance::substance() :
	protein{ 0 }, herb{ 0 }, mineral{ 0 } {
}

Substance_Cell::Substance_Cell(const substance& sub) {
	content = sub;
}
sf::Color Substance_Cell::get_color() const {
	return sf::Color(content.protein, content.herb, content.mineral, 125);
}

Life_Cell::Life_Cell() {
	direction = Matrix::get_default();
}
sf::Color Life_Cell::get_color() const {
	return sf::Color(255, 100, 0, 255);
}
ACTION Life_Cell::think() {
	switch (rand() % 3)
	{
	case 0:
		return ACTION::move;
	case 1:
		return ACTION::rotate_l;
	case 2:
		return ACTION::rotate_r;
	default:
		return ACTION::stay;
	}
}