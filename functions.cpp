#include <SFML/Graphics.hpp>
#include "MenuApi.h"
#include "declarations.h"

void setTextureRect(sf::Sprite &s, int x, int y, bool reversed)
{
	if(reversed)
	{
		s.setTextureRect(sf::IntRect(80 * (x+1), 80 * y, -80, 80));
	}else
	{
		s.setTextureRect(sf::IntRect(80 * x, 80 * y, 80, 80));
	}
}



extern int state;

void createMenu(sf::RenderWindow *wind)
{
	


}