
#include <SFML/Graphics.hpp>

#include "math/math.hpp"
#include "Screen.hpp"
#include "world/World.hpp"

unsigned long long evolution_time = 0;
double DELTA = 0;
World* world;

int main()
{
    srand(time(NULL));
    world = new World(180, 90);
    
    Screen* screen = new Screen(world, 10); screen->set_mode(DISPLAY_MODE::real_color);

    sf::RenderWindow* window = screen->get_window();

    sf::Clock timer;
    while (window->isOpen())
    {
        evolution_time++;

        DELTA = timer.restart().asSeconds();
        std::cout << DELTA << '\t' << evolution_time << '\r';

        for (auto event = sf::Event{}; window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.scancode)
                {
                case sf::Keyboard::Q:
                    screen->set_mode(DISPLAY_MODE::real_color); break;
                case sf::Keyboard::W:
                    screen->set_mode(DISPLAY_MODE::only_bots); break;
                case sf::Keyboard::E:
                    screen->set_mode(DISPLAY_MODE::energy); break;
                default:
                    break;
                }
            }
        }

        world->update();
        screen->draw();
    }
}