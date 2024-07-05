#include "World.hpp"

World::World(int sx, int sy){
	size = Vect(sx, sy);

	map = std::vector(sx, std::vector(sy, nullptr));
}

Vect World::get_size() {
	return size;
}