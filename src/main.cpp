
#include <SFML/Graphics.hpp>

#include "Screen.hpp"
#include "World.hpp"

int main()
{
    World* world = new World(500);
    
    Screen* screen = new Screen(world->get_size(), 1);
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

        screen->draw();
    }
}