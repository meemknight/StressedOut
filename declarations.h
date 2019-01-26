#pragma once
#include <SFML\Graphics.hpp>
#define MAPHEIGHT 20
#define MAPLENGTH 40


void handleEvents(sf::RenderWindow &window);
void setTextureRect(sf::Sprite &s, int x, int y = 0);

enum tiles
{
none,		
woddenFloor,
grass,		 
concreteFloor,
concreteFloor2,
nonelol,
brickWall = 16,
FenceVertically,

};