#pragma once

#include "SFML/Graphics.hpp"
#include "math/math.hpp"

class World;

class Screen {
private:
	World* world;

	sf::RenderWindow window;
	Vect world_size{ 0 };
	int cell_size;

	sf::VertexArray world_grid;
	sf::VertexArray world_cells;
	void draw_world();
	void draw_cell(int px, int py, const sf::Color&);
public:
	Screen(World* world, int one_cell_size);

	sf::RenderWindow* get_window();

	void draw();
};