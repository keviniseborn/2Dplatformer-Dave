#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GamePlay.h"

void main() /*! Entry point for the application */
{
    sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dave the Plumber", sf::Style::Default, settings);
	sf::Clock clock;

	GamePlay Game;
	Game.init();
	while (window.isOpen())
    {
		window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if(clock.getElapsedTime().asMilliseconds() > 50)
		{
			Game.update(clock.getElapsedTime().asSeconds());
			clock.restart();
		}
		window.draw(Game);
		window.display();
    }


}