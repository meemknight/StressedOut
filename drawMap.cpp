#include "drawMap.h"
#include "declarations.h"

extern unsigned char map[MAPLENGTH][MAPHEIGHT];


sf::Sprite mapSprite;


void drawMap(sf::RenderWindow *window)
{
	for(int x=0; x<MAPLENGTH; x++)
	{
		for(int y=0; y<MAPHEIGHT; y++)
		{
			mapSprite.setPosition({ x * 80.f, y * 80.f });
			setTextureRect(mapSprite, map[x][y], 0);
			window->draw(mapSprite);
			
		}
	
	}


}