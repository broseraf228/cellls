#pragma once

#include "SFML/Graphics.hpp"

class Screen {
private:
	sf::RenderWindow window;
	sf::CircleShape world_img;
public:
	Screen(int world_size, float scale);

	sf::RenderWindow* get_window();

	void draw();
};