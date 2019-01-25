#include <SFML/Graphics.hpp>


void setTextureRect(sf::Sprite &s, int x, int y)
{
	s.setTextureRect(sf::IntRect(80 * x, 80 * y, 80, 80));
}