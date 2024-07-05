
#include <SFML/Graphics.hpp>

#include "math/math.hpp"
#include "Screen.hpp"
#include "world/World.hpp"

World* world;

int main()
{
    world = new World(80, 50);
    
    Screen* screen = new Screen(world, 20);
    sf::RenderWindow* window = screen->get_window();

    while (window->isOpen())
    {
        for (auto event = sf::Event{}; window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        world->update();
        screen->draw();
    }
}