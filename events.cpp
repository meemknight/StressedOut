#include <SFML\Graphics.hpp>

bool mouseReleased = 0;

void handleEvents(sf::RenderWindow &window)
{
sf::Event event;
mouseReleased = 0;

while (window.pollEvent(event))
{
	if (event.type == sf::Event::Closed)
		window.close();
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.key.code == sf::Mouse::Left) { mouseReleased = 1; }
	}
}
}

