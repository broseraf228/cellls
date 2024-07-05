#include "Screen.hpp"

#include "world/World.hpp"
#include "world/Cell.hpp"

Screen::Screen(World* world, int one_cell_size){
	this->world = world;
	world_size = world->get_size();
	cell_size = one_cell_size;
	window.create( sf::VideoMode( world_size.x * one_cell_size, world_size.y * one_cell_size ), "CELLLS" );
	window.setFramerateLimit(20);

	world_grid.setPrimitiveType(sf::Lines);
	for (int x = 0; x < world_size.x; x++) {
		world_grid.append(sf::Vertex(sf::Vector2f(x * cell_size, 0), sf::Color::Black));
		world_grid.append(sf::Vertex(sf::Vector2f(x * cell_size, world_size.y * cell_size), sf::Color::Black));
	}
	for (int y = 0; y < world_size.y; y++) {
		world_grid.append(sf::Vertex(sf::Vector2f(0, y * cell_size), sf::Color::Black));
		world_grid.append(sf::Vertex(sf::Vector2f(world_size.x * cell_size, y * cell_size), sf::Color::Black));
	}

	world_cells.setPrimitiveType(sf::Quads);
	world_cells.resize(world_size.x * world_size.y * 4);
}

sf::RenderWindow* Screen::get_window() {
	return &window;
}


void Screen::draw_cell(int px, int py, const sf::Color& color){
	int arrN = (py * world_size.x + px) * 4;
	int left = px * cell_size, top = py * cell_size;
	world_cells[arrN] = sf::Vertex(sf::Vector2f(left, top), color);
	world_cells[arrN + 1] = sf::Vertex(sf::Vector2f(left + cell_size, top), color);
	world_cells[arrN + 2] = sf::Vertex(sf::Vector2f(left + cell_size, top + cell_size), color);
	world_cells[arrN + 3] = sf::Vertex(sf::Vector2f(left, top + cell_size), color);
}
void Screen::draw_world() {
	const auto& map = world->get_map();

	for (int y = 0; y < world_size.y; y++) 
		for (int x = 0; x < world_size.x; x++) {
			if(map[x][y] == nullptr){
				draw_cell(x, y, sf::Color(0, 0, 0, 0));
				continue;}

			draw_cell(x, y, map[x][y]->get_color());
		}
	
}

void Screen::draw() {
	window.clear(sf::Color(180,180,180,255));
	draw_world();
	window.draw(world_grid);
	window.draw(world_cells);
	window.display();
}