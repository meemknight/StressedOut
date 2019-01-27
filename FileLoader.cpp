#include "FileLoader.h"
#include "declarations.h"
#include <fstream>
#include <Windows.h>

extern unsigned char map[MAPLENGTH][MAPHEIGHT];

void loadMap(const char * name)
{
	std::ifstream file(name);

	if (!file.is_open())
	{
		MessageBox(0, "error loading the file", name, 0);
	}

	char c;

	for(int y=0; y<MAPHEIGHT; y++)
	{
		for (int x = 0; x < MAPLENGTH; x++)
		{
			file.get(c);

				map[x][y] = c - '@';
			
		}
		file.get(c);


	}
		
	file.close();

}