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
#include <SFML/Audio.hpp>

unsigned char map[MAPLENGTH][MAPHEIGHT];
extern sf::Sprite mapSprite;


int main()
{	
	srand(time(0));


	sf::RenderWindow window(sf::VideoMode(600, 600), "Stressed Out!", sf::Style::Fullscreen);
	//window.setFramerateLimit(50);
	window.setVerticalSyncEnabled(1);
	int screenWith = window.getSize().x;
	int screenHeight = window.getSize().y;

	sf::Music music;
	music.openFromFile("music.wav");
	music.setLoop(1);
	music.play();


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
	sf::Texture grafitiTexture;

	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	

	mosTexture.loadFromFile("Anim\\mosAnimat.png");
	textures.loadFromFile("textures.png");
	fantomaTexture.loadFromFile("Anim\\fantoma soacra.png");
	copilTexture.loadFromFile("Anim\\plod.png");
	postasTexture.loadFromFile("Anim\\postas.png");
	itemsTextures.loadFromFile("items.png");
	baraTexture.loadFromFile("bar.png");
	angryTexture.loadFromFile("stress.png");
	dolarTexture.loadFromFile("dolar.png");
	colectorTexture.loadFromFile("Anim\\recuperator.png");
	grafitiTexture.loadFromFile("Anim//grafittiKid2.png");

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

	Entity grafer(&grafitiTexture);
	grafer.speed = 0.20f;
	grafer.setPosition({ 22 * 80, 4 * 80 });
	bool graferExists = 1;
	float grafferTime = GetTickCount() + rand() % 15000 + 3000;
	bool graferRetreating = 0;
	float grafferChangeDirectionTime = 0;
	sf::Vector2i graferRetreatingDirection = { 0,0 };
	sf::Vector2i graferAttackingDirection = { 0,0 };


	Entity copil(&copilTexture);
	copil.speed = 0.6;
	copil.setPosition({80 * 14, 4 * 80});
	sf::Vector2i copilDIrection = { 0,0 };
	float copilTime = GetTickCount();

	Entity postas(&postasTexture);
	bool postasExists = 0;
	float postasTime = GetTickCount() + rand() % 12000 + 12000;
	postas.speed = 0.20f;
	float postasMoveTime = GetTickCount();
	postas.setPosition({ 80 * 30 + rand() % 160, -90 });
	bool postasMoves = 1;

	Entity colector(&colectorTexture);
	colector.setPosition(sf::Vector2i((MAPLENGTH - 7) * 80 , (rand()%(80*5))+(80*2)));
	bool collectorActive = 1;
	float collectorTime = GetTickCount() + rand() % 15000; +15000;
	sf::Vector2i collectorDirection = { 0,0 };
	colector.speed = 0.35f;
	float collectorMoveTime = 0;
	bool collectorMoves = 0;

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

	Item money[2] = { &itemsTextures , &itemsTextures };
	money[0].position = sf::Vector2i(23 * 80, 5 * 80);
	money[1].position = sf::Vector2i(23 * 80, 15 * 80);
	
	bool moneyExists[2] = {1,1};
	float moneyTime[2] = { GetTickCount() + rand() % 5000 + 7000,  GetTickCount() + rand() % 5000 + 7000};
	
	for(int i=0; i<sizeof(money)/sizeof(Item); i++)
	{
		setTextureRect(money[i].sprite, items::dolar, 0 );
	}

	Item fork(&itemsTextures);
	fork.setPosition(sf::Vector2i{1 * 80, 2 * 80});
	setTextureRect(fork.sprite, items::fork, 0);

	Item ball(&itemsTextures);
	ball.setPosition(sf::Vector2i(25 * 80, 6 * 80));
	setTextureRect(ball.sprite, items::footBall, 0);
	bool ballExists = 1;
	float ballTime = GetTickCount() + rand() % 10000 + 10000;

	Item club(&itemsTextures);
	setTextureRect(club.sprite, items::club, 0);
	bool clubExists = 0;
	float clubTime = GetTickCount() + rand() % 3000 + 3000;
	sf::Vector2i clubPositions[3] = { {10 * 80, 17 * 80},{7 * 80, 17 * 80},{15 * 80, 2 * 80} };
	
	sf::Sprite currentItemSprite;
	currentItemSprite.setTexture(itemsTextures);
	currentItemSprite.setPosition(sf::Vector2f(10, screenHeight - 40));
	int currentItem = 0;

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
	
	


		fixCollisionWall(mos);
		fixCollision(mos);


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
			pill.draw(&window, deltaTime);

		
		}

		if(GetTickCount() > clubTime)
		{
			if(clubExists)
			{
				clubTime = GetTickCount() + rand() % 4000 + 4000;
				clubExists = 0;
			}else
			{
				clubTime = GetTickCount() + rand() % 8000 + 8000;
				clubExists = 1;
				int count = sizeof(clubPositions) / sizeof(clubPositions[0]);
				int r = rand() % count;
				club.setPosition(clubPositions[r]);
			}
		
		}

		if(clubExists)
		{
			if(colides(&mos, &club))
			{
				clubExists = 0;
				clubTime = GetTickCount() + rand() % 9000 + 9000;
				currentItem = items::club;
			}



			club.calculatePadding(GetTickCount());
			club.draw(&window, deltaTime);
		}


		
		if(GetTickCount() > ballTime)
		{
			if(ballExists)
			{
				ballExists = 0;
				ballTime = GetTickCount() + rand() % 20000 + 15000;
			}else
			{
				ballExists = 1;
				ballTime = GetTickCount() + rand() % 80000 + 8000;
			}
		
		}

		if(ballExists)
		{
			ball.draw(&window, deltaTime);
			
			if(currentItem == items::fork)
			{
				if (colides(&mos, &ball))
				{
					ballExists = 0;
					ballTime = GetTickCount() + rand() % 25000 + 15000;
					currentItem = 0;
					stressValue += BallSP();
				}
			}
				
		}



		if(colides(&mos, &fork))
		{
			currentItem = items::fork;
		}

		fork.calculatePadding(GetTickCount());
		fork.draw(&window, deltaTime);



		for(int i=0; i<sizeof(money) / sizeof(Item); i++)
		{
			if (GetTickCount() > moneyTime[i])
			{
				if (pillExists)
				{
					moneyExists[i] = 0;
					moneyTime[i]= GetTickCount() + rand() % 25000 + 15000;
				}
				else
				{
					moneyExists[i] = 1;
					moneyTime[i] = GetTickCount() + rand() % 15000 + 7000;
				}
			}

			if (moneyExists[i])
			{
				if (colides(&mos, &money[i]))
				{
					moneyExists[i] = 0;
					moneyTime[i] = GetTickCount() + rand() % 15000 + 8000;
					moneyValue += MoneySP();
				}


				money[i].calculatePadding(GetTickCount());
				money[i].draw(&window, deltaTime);


			}
		}




#pragma region Collector
		
		if(GetTickCount() > collectorTime)
		{
			if(collectorActive)
			{
					
			}else
			{

				colector.setPosition(sf::Vector2i(80 * (MAPLENGTH - 2), rand() % 1000 + 10));
				collectorMoveTime = rand() % 2000 + 1000;
				collectorDirection = { -1, 0 };
				collectorActive = 1;
			}
		}
		
		if(collectorActive)
		{
			if (mos.getPosition().x >= (GARDENSTART - 1) * 80)
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
				//collectorDirection = { 0,0 };
				if (GetTickCount() > collectorMoveTime)
				{
					collectorMoveTime = GetTickCount() + rand() % 3000;
					if (collectorMoves) { collectorMoves = 0; collectorDirection = { 0,0 }; }
					else
					{
						collectorMoves = 1;
						int r = rand() % 5;
						if (r == 0)
						{
							collectorDirection.x = 0;
						}
						else if (r == 1)
						{
							collectorDirection.x = -1;
						}
						else
						{
							collectorDirection.x = 1;
						}

						r = rand() % 3;
						if (r == 0)
						{
							collectorDirection.y = 1;
						}
						else if (r == 1)
						{
							collectorDirection.y = -1;
						}
						else
						{
							collectorDirection.y = 0;
						}
					}

				}
			}

			if (colector.getPosition().x < (GARDENSTART - 1) * 80)
			{
				if (collectorDirection.x == -1)
				{
					collectorDirection.x = 1;
				}
			}

			colector.autoMove(collectorDirection, deltaTime);
			fixCollision(colector);

			
			colector.draw(&window, deltaTime);
		}

		if(colector.position.y < -70 || colector.position.y > (MAPHEIGHT-1) * 80 || colector.position.x > MAPLENGTH * 80)
		{
			collectorActive = 0;
			collectorTime = GetTickCount() + rand() % 21000 + 12000;
			colector.setPosition(sf::Vector2i((MAPLENGTH - 7) * 80, (rand() % (80 * 5)) + (80 * 2)));
		}

		if(collectorActive)
		{
			if (colides(&mos, &colector))
			{
				moneyValue += CollectorSPS() * deltaTime;
			}
		}
		
	
		

#pragma endregion



		if (GetTickCount() > copilTime)
		{
			copilTime = GetTickCount() + rand() % 1000 + 100;
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
			postas.draw(&window, deltaTime);
			
			if (colides(&mos, &postas)) 
			{
				moneyValue += PostasSPS() * deltaTime;
			}

		}else if(GetTickCount() > postasTime )
		{
			postasExists = 1;
		}

		if(postas.getPosition().y > MAPHEIGHT * 80 + 20)
		{
			postasExists = 0;
			postasTime = GetTickCount() + rand() % 15000 + 5000;
			postas.setPosition({ 80 * 30 + rand() % 160, -90 });
		}


		copil.autoMove(copilDIrection, deltaTime);

		fixCollisionWall(copil);
		fixCollision(copil);
		copil.draw(&window, deltaTime);


#pragma region grafer

		if(GetTickCount() > grafferTime)
		{
			grafferTime = GetTickCount() + rand() % 12000 + 10000;
			if (!graferExists)
			{
				graferExists = 1;
				graferRetreating = 0;
			}else
			{
				graferRetreating = 1;
				int r = rand() % 2;
				if(r==0)
				{
					graferRetreatingDirection = { 1, -1 };
				}else
				{
					graferRetreatingDirection = { 1, 1 };
				}
			}
		}

		if(graferExists)
		{

			if(!graferRetreating)
			{
				stressValue += GrafferSPS() * deltaTime;
			}


			if(colides(&mos, &grafer))
			{
				if(currentItem == items::club && !graferRetreating)
				{
					graferRetreating = 1;
					currentItem = 0;
					stressValue += GrafferBeatSP();
				}
			}



			if(graferRetreating)
			{
				grafer.autoMove(graferRetreatingDirection, deltaTime);
				grafer.speed = 0.50f;
			}else
			{
				grafer.speed = 0.20f;

				if (grafer.getPosition().x > (GARDENSTART + 5) * 80)
				{
					graferAttackingDirection.x = -1;
				}

				if(grafer.getPosition().x < (GARDENSTART - 1) * 80)
				{
					graferAttackingDirection.x = 1;
					grafer.autoMove(graferAttackingDirection, deltaTime);
				}else
				if(abs(mos.getPosition().x - grafer.getPosition().x) > 80 * 3)
				{
					//graferAttackingDirection.x = -1;
					grafer.autoMove(graferAttackingDirection, deltaTime);
				}else
				{
					//graferAttackingDirection.x = 1;
					grafer.autoMove(graferAttackingDirection, deltaTime);
				}

			}
			
			if(GetTickCount() > grafferChangeDirectionTime)
			{ 
				grafferChangeDirectionTime = GetTickCount() + rand() % 4000 + 2000;
				int r = rand() % 3;
				if (r == 0)
				{
					graferAttackingDirection.y = 1;
				}
				else if (r == 1)
				{
					graferAttackingDirection.y = -1;

				} else 
				{
					graferAttackingDirection.y = 0;
				}
			}

			if(!graferRetreating)
			{
				fixCollisionWall(grafer);
			}else
			if (grafer.position.y < -70 || grafer.position.y >(MAPHEIGHT - 1) * 80 || grafer.position.x > MAPLENGTH * 80)
			{
				graferExists = 0;
				grafferTime = GetTickCount() + rand() % 15000 + 6000;
				grafer.setPosition(sf::Vector2i((MAPLENGTH - 7) * 80, (rand() % (80 * 5)) + (80 * 2)));
			}

			if(graferExists)
			{
				fixCollision(grafer);
				grafer.draw(&window, deltaTime);
			}
			
		}

		


#pragma endregion

		moneyValue += moneySPS() * deltaTime;



#pragma region Fantoma
		//fantoma
		if (GetTickCount() > fantomaTime)
		{
			fantomaTime = (rand() % 25000) + 5000 + GetTickCount();
			if (fantomaAwake)
			{
				fantomaAwake = 0;
			}
			else
			{
				fantomaAwake = 1;
			}

			fantoma.setPosition({ 20 * 80, 80 });
		}

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

			if (fantoma.getPosition().x >= (GARDENSTART-1) * 80)
			{
				//if (fantomaDirection.x == 1)
				{
					fantomaDirection.x = -1;
				}
			}

			fantoma.autoMove(fantomaDirection, deltaTime);

			fixCollisionWall(fantoma);
			fantoma.draw(&window, deltaTime);

			if (colides(&mos, &fantoma))
			{
				stressValue += GhostSPS() * deltaTime;
			}
		}
#pragma endregion



		window.setView(view);
		mos.draw(&window, deltaTime);
		
		if (moneyValue > 100.f) { moneyValue = 100; }
		if (moneyValue <= 0) { moneyValue = 0; stressValue += moneySPS() * deltaTime; }

		if (stressValue > 100.f) { stressValue = 100; }
		if (stressValue <= 0) { stressValue = 0; }
		stressBar.padding = {(int)view.getCenter().x - screenWith / 2, (int)view.getCenter().y - screenHeight /2};
		stressBar.draw(&window);

		
		moneyBar.padding = { (int)view.getCenter().x - screenWith / 2, (int)view.getCenter().y - screenHeight / 2 };
		moneyBar.draw(&window);

		setTextureRect(currentItemSprite, currentItem, 0);
		currentItemSprite.setPosition(sf::Vector2f{ (float)view.getCenter().x - screenWith / 2 + 10, (float)view.getCenter().y - screenHeight / 2 + screenHeight - 80 });
		window.draw(currentItemSprite);

		window.display();

		//std::cout << colector.getPosition().x / 80 << " " << colector.getPosition().y /80 << " "<< mos.getPosition().x /80 <<" " << mos.getPosition().y/80 <<" " << collectorActive <<"\n";
		
		window.clear();
	}

	return 0;
}