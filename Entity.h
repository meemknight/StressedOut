#pragma once
#include <SFML/Graphics.hpp>
#include "declarations.h"	

class Entity
{
public:
	Entity() = default;
	Entity(sf::Texture *texture)
	{
		sprite.setTexture(*texture);
	}

	float speed;

	sf::Sprite sprite;
	
	sf::Vector2i position;
	sf::Vector2i lastpos;
	bool movingright;
	bool movingdown;

	void setPosition(sf::Vector2i p)
	{
		position = p;
	}
	
	sf::Vector2i getPosition()
	{
		return position;
	}

	float getcenterx()
	{
		return position.x + 40;
	}

	float getcentery()
	{
		return position.y + 40;
	}

	sf::Vector2f sizeofentity = {80.f,80.f};

	virtual void draw(sf::RenderWindow *window)
	{
		sprite.setPosition({(float)position.x, (float)position.y});
		//lastpos = position;
		window->draw(sprite);
	}

	void autoMove(sf::Vector2i deplasation, float deltaTime)
	{
		if (deplasation.x != 0 && deplasation.y != 0)
		{
			setPosition({ getPosition().x + (int)(deplasation.x * deltaTime * speed / (float)sqrt(2)), getPosition().y + (int)(deplasation.y * deltaTime * speed / (float)sqrt(2)) });
		}
		else
		{
			setPosition({ getPosition().x + (int)(deplasation.x * deltaTime * speed), getPosition().y + (int)(deplasation.y * deltaTime * speed) });
		}
	}
};

void fixCollision(Entity &entity);
void fixCollisionWall(Entity &entity);
void updateMovement(Entity &entity);
bool colides(Entity *a, Entity *b);


class Item: public Entity
{
public:
	Item() = default;
	Item(sf::Texture *t) { sprite.setTexture(*t); };

	
	float paddingPosition = 0;

	void calculatePadding(float time);

	virtual void draw(sf::RenderWindow *window)override;

};



