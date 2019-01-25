#include <SFML/Graphics.hpp>
#include "declarations.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		handleEvents(window);
		


		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}