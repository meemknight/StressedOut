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
	std::string str;
	if (sec == 0)
	{
		str = "00:00";
	}
	else
	{
		int minute = sec / 60;
		int restSec = sec % 60;
		std::string strMin, strSec;
		strMin = int_to_str(minute);
		strSec = int_to_str(restSec);
		if (minute < 10)
		{
			strMin = "0" + int_to_str(minute);
		}
		if (restSec < 10)
		{
			strSec = "0" + int_to_str(restSec);
		}

		if (minute == 0)
		{
			str = "00:" + strSec;
		}
		else if (restSec == 0)
		{
			str = strMin + ":00";
		}
		else
		{
			str = strMin + ":" + strSec;
		}
	}
	return str;
}

void createMenu(sf::RenderWindow *wind)
{



}