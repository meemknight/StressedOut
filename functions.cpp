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

std::string int_to_str(int integer)
{
	std::string str = "";
	while (integer)
	{
		str += integer % 10 + '0';
		integer /= 10;
	}
	std::reverse(str.begin(), str.end());
	return str;
}

std::string minute_sec(int sec)
{
	int minute = sec / 60;
	int restSec = sec % 60;
	std::string str;
	if (minute == 0)
	{
		str = "00:" + int_to_str(restSec);
	}
	else
	{
		str = int_to_str(minute) + ":" + int_to_str(restSec);
	}

	return str;
}

void createMenu(sf::RenderWindow *wind)
{



}