#include "Screen.hpp"

Screen::Screen(int world_size, float scale){
	window.create( sf::VideoMode( world_size * scale * 2, world_size * scale * 2 ), "CELLLS" );
	window.setFramerateLimit(144);

	world_img = sf::CircleShape(world_size * scale);
	world_img.setOrigin(world_size * scale, world_size * scale);
	world_img.setPosition(world_size * scale, world_size * scale);
}

sf::RenderWindow* Screen::get_window() {
	return &window;
}

void Screen::draw() {
	window.clear();
	window.draw(world_img);
	window.display();
}