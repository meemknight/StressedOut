
#pragma once
#include <SFML/Graphics.hpp>

class Bar
{
public:
	Bar() = default;
	Bar(sf::Texture *bar, sf::Texture *item, sf::Color c, sf::Vector2i position);

	float *value;



	sf::Sprite barSprite;
	sf::Sprite itemSprite;
	sf::RectangleShape rectFront;
	sf::RectangleShape rectBack;

	sf::Vector2i position;
	sf::Vector2i padding;


	void draw(sf::RenderWindow *window);

};



