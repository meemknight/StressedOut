#include <SFML/Graphics.hpp>
#include "declarations.h"
#include "Entity.h"
#include <iostream>
#include "FileLoader.h"
#include "drawMap.h"
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include "Bar.h"
#include "Stress.h"

unsigned char map[MAPLENGTH][MAPHEIGHT];
extern sf::Sprite mapSprite;


int main()
{	
	srand(time(0));


	sf::RenderWindow window(sf::VideoMode(200, 200), "Stressed Out!", sf::Style::Fullscreen);
	//window.setFramerateLimit(50);
	window.setVerticalSyncEnabled(1);
	int screenWith = window.getSize().x;
	int screenHeight = window.getSize().y;


	sf::Texture mosTexture;
	sf::Texture textures;
	sf::Texture fantomaTexture;
	sf::Texture copilTexture;
	sf::Texture postasTexture;
	sf::Texture itemsTextures;
	sf::Texture baraTexture;
	sf::Texture angryTexture;
	sf::Texture dolarTexture;
	sf::Texture colectorTexture;

	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	

	mosTexture.loadFromFile("mos.png");
	textures.loadFromFile("textures.png");
	fantomaTexture.loadFromFile("fantoma soacra.png");
	copilTexture.loadFromFile("copil.png");
	postasTexture.loadFromFile("postas.png");
	itemsTextures.loadFromFile("items.png");
	baraTexture.loadFromFile("bar.png");
	angryTexture.loadFromFile("stress.png");
	dolarTexture.loadFromFile("dolar.png");
	colectorTexture.loadFromFile("recuperator.png");

	mapSprite.setTexture(textures);
	

	Bar stressBar(&baraTexture, &angryTexture, sf::Color::Red ,{screenWith - 80 * 6, screenHeight - 100 * 1});
	float stressValue = 100;
	float moneyValue = 100;
	stressBar.value = &stressValue;

	Bar moneyBar(&baraTexture, &dolarTexture, sf::Color::Green, { screenWith - 80 * 6, screenHeight - 50 * 1 });
	moneyBar.value = &moneyValue;

	loadMap("map.txt");
	
	
	Entity fantoma(&fantomaTexture);
	fantoma.speed = 0.20f;
	fantoma.setPosition({ 20 * 80, 80 });
	float fantomaTime = (rand() %35000) + 5000 + GetTickCount();
	bool fantomaAwake = 1;
	float fantomaMoveTime = GetTickCount();
	bool fantomaMoves = 1;
	sf::Vector2i fantomaDirection = { 0,0 };
	//fantoma

	Entity copil(&copilTexture);
	copil.speed = 0.6;
	copil.setPosition({80 * 14, 4 * 80});
	sf::Vector2i copilDIrection = { 0,0 };
	float copilTime = GetTickCount();

	Entity postas(&postasTexture);
	bool postasExists = 0;
	float postasTime = GetTickCount() + rand() % 12000 + 10000;
	postas.speed = 0.20f;
	float postasMoveTime = 0;
	postas.setPosition({ 80 * 34 + rand() % 160, -90 });
	bool postasMoves = 1;

	Entity colector(&colectorTexture);
	colector.setPosition(sf::Vector2i((MAPLENGTH - 5) * 80 + 80, rand()%(80*5)+(80*2)));
	bool collectorActive = 1;
	float collectorTime = GetTickCount() + rand() % 10000; +10000;
	sf::Vector2i collectorDirection = { 0,0 };
	colector.speed = 0.35f;

	Entity mos(&mosTexture);
	mos.position = { 100,100 };
	mos.speed = 0.45f;

	float time = GetTickCount();
	float deltaTime = 0;



	Item pill(&itemsTextures);
	setTextureRect(pill.sprite, 2, 0);
	pill.setPosition({ 1 * 80, 17 * 80 });
	bool pillExists = 1;
	float pillTime = GetTickCount() + rand() % 5000 + 7000;


	while (window.isOpen())
	{


		deltaTime = GetTickCount() - time;
		time = GetTickCount();
		//deltaTime = 0.01;

		handleEvents(window);
		
		//handle key

		sf::Vector2i deplasation = { 0,0 };
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			deplasation.x += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			deplasation.x -= 1;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			deplasation.y -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			deplasation.y += 1;
		}
			
		if(deplasation.x != 0 && deplasation.y !=0)
		{
			mos.setPosition({ mos.getPosition().x + (int)(deplasation.x * deltaTime * mos.speed / (float)sqrt(2)), mos.getPosition().y + (int)(deplasation.y * deltaTime * mos.speed / (float)sqrt(2)) });
		}else
		{
			mos.setPosition({ mos.getPosition().x + (int)(deplasation.x * deltaTime * mos.speed), mos.getPosition().y + (int)(deplasation.y * deltaTime * mos.speed)});
		}

		//view.setViewport(sf::FloatRect( mos.sprite.getPosition().x - (window.getSize().x /2.f), mos.sprite.getPosition().y - (window.getSize().y / 2.f), window.getSize().x, window.getSize().y ));
	
		//fantoma
		if(GetTickCount() > fantomaTime)
		{
			fantomaTime = (rand() % 25000) + 5000 + GetTickCount();
			if(fantomaAwake)
			{
				fantomaAwake = 0;
			}else
			{
				fantomaAwake = 1;
			}

			fantoma.setPosition({ 20 * 80, 80 });
		}


		fixCollisionWall(mos);
		fixCollision(mos);
		updateMovement(mos);


		view.setCenter((int)mos.getPosition().x, (int)mos.getPosition().y);

		if (view.getCenter().x < screenWith / 2.f) { view.setCenter((int)(screenWith / 2.f), (int)view.getCenter().y); }
		if (view.getCenter().x > -(screenWith / 2.f) + (80 * MAPLENGTH)) { view.setCenter((int)(-(screenWith / 2.f) + (80 * MAPLENGTH)), (int)view.getCenter().y); }
		if (view.getCenter().y < screenHeight / 2.f) { view.setCenter((int)(view.getCenter().x), (int)(screenHeight / 2.f)); }
		if (view.getCenter().y > -(screenHeight / 2.f) + (80 * MAPHEIGHT)) { view.setCenter((int)(view.getCenter().x), (int)(-(screenHeight / 2.f) + (80 * MAPHEIGHT))); }
		///fix screen position ^


		drawMap(&window);


		if(GetTickCount() > pillTime)
		{
			if(pillExists)
			{
				pillExists = 0;
				pillTime = GetTickCount() + rand()%10000 + 15000;
			}else
			{
				pillExists = 1;
				pillTime = GetTickCount() + rand() % 10000 + 5000;
			}
		}

		if(pillExists)
		{
			if(colides(&mos, &pill))
			{
				pillExists = 0;
				pillTime = GetTickCount() + rand() % 10000 + 15000;
				stressValue += PillSP();
			}


			pill.calculatePadding(GetTickCount());
			pill.draw(&window);

		
		}




#pragma region Fantoma
		if (fantomaAwake)
		{

			if (mos.getPosition().x < GARDENSTART * 80)
			{
				if (abs(mos.getcenterx() - fantoma.getcenterx()) < 30)
				{
					fantomaDirection.x = 0;
				}
				else if (mos.getPosition().x > fantoma.getPosition().x)
				{
					fantomaDirection.x = 1;
				}
				else
				{
					fantomaDirection.x = -1;
				}
				if (abs(mos.getcentery() - fantoma.getcentery()) < 30)
				{
					fantomaDirection.y = 0;
				}
				else if (mos.getPosition().y > fantoma.getPosition().y)
				{
					fantomaDirection.y = 1;
				}
				else
				{
					fantomaDirection.y = -1;
				}

			}
			else
			{
				if (GetTickCount() > fantomaMoveTime)
				{
					fantomaMoveTime += rand() % 3000 + 1000;
					if (fantomaMoves) { fantomaMoves = 0; fantomaDirection = { 0,0 }; }
					else
					{
						fantomaMoves = 1;
						int r = rand() % 3;
						if (r == 0)
						{
							fantomaDirection.x = 1;
						}
						else if (r == 1)
						{
							fantomaDirection.x = -1;
						}
						else
						{
							fantomaDirection.x = 0;
						}

						r = rand() % 3;
						if (r == 0)
						{
							fantomaDirection.y = 1;
						}
						else if (r == 1)
						{
							fantomaDirection.y = -1;
						}
						else
						{
							fantomaDirection.y = 0;
						}
					}

				}
				
				

			}

			if (fantoma.getPosition().x >= (GARDENSTART - 1) * 80)
			{
				if (fantomaDirection.x == 1)
				{
					fantomaDirection.x = -1;
				}
			}

			fantoma.autoMove(fantomaDirection, deltaTime);

			fixCollisionWall(fantoma);
			updateMovement(fantoma);
			fantoma.draw(&window);

			if (colides(&mos, &fantoma))
			{
				stressValue += GhostSPS() * deltaTime;
			}
		}
#pragma endregion
	
#pragma region Collector
		
		if(GetTickCount() > collectorTime)
		{
			if(collectorActive)
			{
					
			}else
			{
				collectorActive = 1;
			}
		}
		
		if (mos.getPosition().x > GARDENSTART * 80)
		{
			if (abs(mos.getcenterx() - colector.getcenterx()) < 30)
			{
				collectorDirection.x = 0;
			}
			else if (mos.getPosition().x > colector.getPosition().x)
			{
				collectorDirection.x = 1;
			}
			else
			{
				collectorDirection.x = -1;
			}
			if (abs(mos.getcentery() - colector.getcentery()) < 30)
			{
				collectorDirection.y = 0;
			}
			else if (mos.getPosition().y > colector.getPosition().y)
			{
				collectorDirection.y = 1;
			}
			else
			{
				collectorDirection.y = -1;
			}
		}
		else 
		{
			collectorDirection = { 0,0 };
		}

		//if (colector.getPosition().x < (GARDENSTART - 1) * 80)
		//{
		//	if (collectorDirection.x == -1)
		//	{
		//		collectorDirection.x = 1;
		//	}
		//}

		colector.autoMove(collectorDirection, deltaTime);

		updateMovement(colector);
		colector.draw(&window);

		if (colides(&mos, &colector))
		{
			moneyValue += CollectorSPS() * deltaTime;
		}
	
		

#pragma endregion


		if (GetTickCount() > copilTime)
		{
			copilTime = GetTickCount() + rand() % 500;
			int r = rand() % 3;
			if (r == 0)
			{
				copilDIrection.x = 1;
			}
			else if (r == 1)
			{
				copilDIrection.x = -1;
			}
			else
			{
				copilDIrection.x = 0;
			}

			r = rand() % 3;
			if (r == 0)
			{
				copilDIrection.y = 1;
			}
			else if (r == 1)
			{
				copilDIrection.y = -1;
			}
			else
			{
				copilDIrection.y = 0;
			}

		}

		if (copil.getPosition().x >= (GARDENSTART -1 ) * 80)
		{
			if (copilDIrection.x == 1)
			{
				copilDIrection.x = -1;
			}
		}

		if(colides(&mos, &copil))
		{
			stressValue += ChildSPS();
		}


		if(postasExists)
		{
			if(postasMoves)
			{
				postas.autoMove({ 0,1 }, deltaTime);
			}
			
			if(GetTickCount() > postasMoveTime)
			{
				postasMoveTime = GetTickCount() + rand() % 4000;
				if(postasMoves)
				{
					postasMoves = 0;
				}else
				{
					postasMoves = 1;
				}
			}

			//fixCollisionWall(postas);
			fixCollision(postas);
			updateMovement(postas);
			postas.draw(&window);
		
		}else if(GetTickCount() > postasTime )
		{
			postasExists = 1;
		}

		if(postas.getPosition().y > MAPHEIGHT * 80 + 20)
		{
			postasExists = 0;
			postasTime = GetTickCount() + rand() % 15000 + 10000;
			postas.setPosition({ 80 * 34 + rand() % 160, -90 });
		}

		


		copil.autoMove(copilDIrection, deltaTime);

		fixCollisionWall(copil);
		fixCollision(copil);
		updateMovement(copil);
		copil.draw(&window);

		window.setView(view);
		mos.draw(&window);
		
		
		if (stressValue > 100.f) { stressValue = 100; }
		stressBar.padding = {(int)view.getCenter().x - screenWith / 2, (int)view.getCenter().y - screenHeight /2};
		stressBar.draw(&window);

		moneyBar.padding = { (int)view.getCenter().x - screenWith / 2, (int)view.getCenter().y - screenHeight / 2 };
		moneyBar.draw(&window);

		window.display();

		window.clear();
	}

	return 0;
}