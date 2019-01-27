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
#include "MenuApi.h"
#include <fstream>

unsigned char map[MAPLENGTH][MAPHEIGHT];
extern sf::Sprite mapSprite;
int state = states::mainMenu;
extern bool mouseReleased;
ma::Menu mainM;
sf::Texture bigbuttonBrickTexture;
sf::Texture textButtonTexture;
sf::Texture smallButtonBrickTexture;
sf::Texture buttonBrickTexture;
sf::Texture backgroundBrick;
sf::Texture backButton;
sf::Font font;
sf::Music music;


float stressValue = 100;
float moneyValue = 100;

float timeaCount = clock() / 1000;
float timebCount = clock() / 1000;
	  
int highSchore = 123;

int currentItem = 0;

	Entity fantoma;
	float fantomaTime = (rand() %35000) + 5000 + GetTickCount();
	bool fantomaAwake = 0;
	float fantomaMoveTime = GetTickCount();
	bool fantomaMoves = 1;
	sf::Vector2i fantomaDirection = { 0,0 };
	bool fantomaReturns = 0;

	Entity grafer;
	
	
	bool graferExists = 1;
	float grafferTime = GetTickCount() + rand() % 15000 + 3000;
	bool graferRetreating = 0;
	float grafferChangeDirectionTime = 0;
	sf::Vector2i graferRetreatingDirection = { 0,0 };
	sf::Vector2i graferAttackingDirection = { 0,0 };

	Entity copil;
	sf::Vector2i copilDIrection = { 0,0 };
	float copilTime = GetTickCount();

	Entity postas;
	bool postasExists = 0;
	float postasTime = GetTickCount() + rand() % 12000 + 12000;
	float postasMoveTime = GetTickCount();
	bool postasMoves = 1;

	Entity colector;
	bool collectorActive = 1;
	float collectorTime = GetTickCount() + rand() % 15000;
	sf::Vector2i collectorDirection = { 0,0 };
	float collectorMoveTime = 0;
	bool collectorMoves = 0;

	Entity mos;

	bool flowerExists = 0;
	float flowerTime = GetTickCount() + rand() % 1000 + 1000;

	bool pillExists = 1;
	float pillTime = GetTickCount() + rand() % 5000 + 7000;

void resetGame()
{
	currentItem = 0;

	stressValue = 100;
	moneyValue = 100;
	timeaCount = clock() / 1000;
	timebCount = clock() / 1000;

	fantoma.setPosition({ 20 * 80, 80 });
	 fantomaTime = (rand() % 35000) + 5000 + GetTickCount();
	 fantomaAwake = 0;
	 fantomaMoveTime = GetTickCount();
	 fantomaMoves = 1;
	 fantomaDirection = { 0,0 };
	 fantomaReturns = 0;

	 grafer.setPosition({ 32 * 80, 4 * 80 });
	  graferExists = 0;
	  grafferTime = GetTickCount() + rand() % 15000 + 3000;
	  graferRetreating = 0;
	  grafferChangeDirectionTime = 0;
	  graferRetreatingDirection = { 0,0 };
	  graferAttackingDirection = { 0,0 };

	  copil.setPosition({ 80 * 14, 4 * 80 });
	   copilDIrection = { 0,0 };
	  copilTime = GetTickCount();

	  postasExists = 0;
	  postasTime = GetTickCount() + rand() % 12000 + 12000;
	  postasMoveTime = GetTickCount();
	  postasMoves = 1;
	  postas.setPosition({ 80 * 30 + rand() % 160, -90 });


	  colector.setPosition(sf::Vector2i((MAPLENGTH - 7) * 80, (rand() % (80 * 5)) + (80 * 2)));
	   collectorActive = 0;
	  collectorTime = GetTickCount() + rand() % 15000;
	  collectorDirection = { 0,0 };
	  collectorMoveTime = 0;
	  collectorMoves = 0;

	  mos.position = { 100,100 };

	  flowerExists = 0;
	  flowerTime = GetTickCount() + rand() % 1000 + 1000;

	  pillExists = 1;
	  pillTime = GetTickCount() + rand() % 5000 + 7000;
	  
}

void play()
{
	resetGame();
	state = states::game;
}


void musicOn()
{
	music.play();
}

void musicOff()
{
	music.pause();
}


int main()
{
	srand(time(0));

	{
		std::ifstream f;
		f.open("score.txt");
		f >> highSchore;
		f.close();
	}

	//save menue
	class RAII_
	{
	public:
		void(*fp)();

		~RAII_()
		{
			fp();
		}
	}raii_({[] 
	{
		std::ofstream f("score.txt");
		f << highSchore;
		f.close();
	}});


	sf::RenderWindow window(sf::VideoMode(600, 600), "Stressed Out!", sf::Style::Fullscreen);
	//window.setFramerateLimit(50);
	window.setVerticalSyncEnabled(1);
	int screenWith = window.getSize().x;
	int screenHeight = window.getSize().y;

	createMenu(&window);

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
	
	stressBar.value = &stressValue;

	Bar moneyBar(&baraTexture, &dolarTexture, sf::Color::Green, { screenWith - 80 * 6, screenHeight - 50 * 1 });
	moneyBar.value = &moneyValue;

	sf::Text ceasText;
	ceasText.setPosition(100, 100);
	ceasText.setCharacterSize(80);
	ceasText.setFont(font);

	loadMap("map.txt");
	
	
	fantoma.sprite.setTexture(fantomaTexture);
	fantoma.speed = 0.21f;
	
	//fantoma

	

	grafer.sprite.setTexture(grafitiTexture);
	grafer.speed = 0.20f;


	copil.sprite.setTexture(copilTexture);
	copil.speed = 0.6;

	
	postas.sprite.setTexture(postasTexture);
	postas.speed = 0.20f;
	

	colector.sprite.setTexture(colectorTexture);
	colector.speed = 0.35f;



	mos.sprite.setTexture(mosTexture);
	mos.speed = 0.45f;

	float time = GetTickCount();
	float deltaTime = 0;
	
	Item pill(&itemsTextures);
	setTextureRect(pill.sprite, 2, 0);
	pill.setPosition({ 1 * 80, 17 * 80 });
	

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
	bool forkExists = 0;
	float forkTime = GetTickCount() + rand() % 10000 + 1000;

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
	
	Item flower(&itemsTextures);
	setTextureRect(flower.sprite, items::flower, 0);
	
	sf::Vector2i flowerPositions[4] = { {24*80,2*80},{23*80,2*80},{24*80,18*80},{23*80, 18*80} };

	sf::Sprite currentItemSprite;
	currentItemSprite.setTexture(itemsTextures);
	currentItemSprite.setPosition(sf::Vector2f(10, screenHeight - 40));

	

#pragma region meniu

	textButtonTexture.loadFromFile("menu//textButton.png");
	smallButtonBrickTexture.loadFromFile("menu//smallButtonBrick.png");
	buttonBrickTexture.loadFromFile("menu//ButtonBrick.png");
	backgroundBrick.loadFromFile("menu//backgroundBrick.png");
	backButton.loadFromFile("menu//backButton.png");
	bigbuttonBrickTexture.loadFromFile("menu//BigButtonBrick.png");
	font.loadFromFile("slkscr.ttf");


	mainM.backButton = new ma::IconButton(0, &backButton, 0);
	mainM.background.setTexture(backgroundBrick);
	mainM.window = &window;

	sf::Texture ghostTexturePrev;
	ghostTexturePrev.loadFromFile("menu//ghost.png");
	sf::Texture copilTexturePrev;
	copilTexturePrev.loadFromFile("menu//kid.png");
	sf::Texture grafitiTexturePrev;
	grafitiTexturePrev.loadFromFile("menu//grafiti.png");
	sf::Texture postmanTexturePrev;
	postmanTexturePrev.loadFromFile("menu//Postman.png");
	sf::Texture colectorTexturePrev;
	colectorTexturePrev.loadFromFile("menu//TaxCollector.png");

	ma::MenuHolder* holder = new ma::MenuHolder;
	holder->menu = &mainM;
	
	ma::MenuHolder* optionMeniu = new ma::MenuHolder;
	optionMeniu->menu = &mainM;

	ma::MenuHolder* HowToPlay = new ma::MenuHolder;
	HowToPlay->menu = &mainM;

	ma::MenuHolder *GeneralInfo = new ma::MenuHolder;
	GeneralInfo->menu = &mainM;
	ma::ButtonGroup *gr1 = new ma::ButtonGroup(&mainM);
	gr1->appendElement(new ma::TextButton(&bigbuttonBrickTexture, font,0, "You are an\nold man.\nYour goal\nis to not\nget stressed\nout by others.\nTry to take your\npills and always\nkeep an eye ouy\nfor money", 50));
	gr1->appendElement(new ma::TextButton(&mosTexture, font, 0 , " "));
	GeneralInfo->appendElement(gr1);

	ma::MenuHolder *Child = new ma::MenuHolder;
	Child->menu = &mainM;
	ma::ButtonGroup *gr2 = new ma::ButtonGroup(&mainM);
	gr2->appendElement(new ma::TextButton(&bigbuttonBrickTexture, font, 0, "This little\nturd is always\nannoying you.\nTry not to get\nin thoch to him."));
	gr2->appendElement(new ma::TextButton(&copilTexturePrev, font, 0, ""));
	Child->appendElement(gr2);

	ma::MenuHolder *TaxCollector = new ma::MenuHolder;
	TaxCollector->menu = &mainM;
	ma::ButtonGroup *gr3 = new ma::ButtonGroup(&mainM);
	gr3->appendElement(new ma::TextButton(&bigbuttonBrickTexture, font, 0, "This is a\nbad person.\nHe wants\nyour money.\nWhen you see\nhim, try to\nhide inside."));
	gr3->appendElement(new ma::TextButton(&colectorTexturePrev, font, 0, ""));
	TaxCollector->appendElement(gr3);

	ma::MenuHolder *Ghost = new ma::MenuHolder;
	Ghost->menu = &mainM;
	ma::ButtonGroup *gr4 = new ma::ButtonGroup(&mainM);
	gr4->appendElement(new ma::TextButton(&bigbuttonBrickTexture, font, 0, "This is your\nmother in law's\nghost.\nDon't even try\ntalking to her.\n(also,\nshe likes\nflowers)"));
	gr4->appendElement(new ma::TextButton(&ghostTexturePrev, font, 0, ""));
	Ghost->appendElement(gr4);

	ma::MenuHolder *Postas = new ma::MenuHolder;
	Postas->menu = &mainM;
	ma::ButtonGroup *gr5 = new ma::ButtonGroup(&mainM);
	gr5->appendElement(new ma::TextButton(&bigbuttonBrickTexture, font, 0, "This is the/npostman./nHe gives you/nmoney."));
	gr5->appendElement(new ma::TextButton(&postmanTexturePrev, font, 0, ""));
	Postas->appendElement(gr5);

	ma::MenuHolder *Grafitty = new ma::MenuHolder;
	Grafitty->menu = &mainM;
	ma::ButtonGroup *gr6 = new ma::ButtonGroup(&mainM);
	gr6->appendElement(new ma::TextButton(&bigbuttonBrickTexture, font, 0, "This a******\nis painting your\nwalls.\nJust get a\nclub and beat\nthe s***\nout of him.\nAlso, if you\ndont, you\nwill get stressed.", 50));
	gr6->appendElement(new ma::TextButton(&grafitiTexturePrev, font, 0, ""));
	Grafitty->appendElement(gr6);

	HowToPlay->appendElement(new ma::TextButton(&buttonBrickTexture, font, GeneralInfo, "General info"));
	HowToPlay->appendElement(new ma::TextButton(&buttonBrickTexture, font, Child, "Child (plod)"));
	HowToPlay->appendElement(new ma::TextButton(&buttonBrickTexture, font, TaxCollector, "Tax Collector"));
	HowToPlay->appendElement(new ma::TextButton(&buttonBrickTexture, font, Ghost, "Ghost"));
	HowToPlay->appendElement(new ma::TextButton(&buttonBrickTexture, font, Postas, "Post Man"));
	HowToPlay->appendElement(new ma::TextButton(&buttonBrickTexture, font, Grafitty, "Grafitty Guy"));


	ma::ButtonGroup* soundGroup = new ma::ButtonGroup;
	soundGroup->menu = &mainM;

	soundGroup->appendElement(new ma::TextButton(&smallButtonBrickTexture, font, new ma::Function(musicOn), "ON"));
	soundGroup->appendElement(new ma::TextButton(&smallButtonBrickTexture, font, new ma::Function(musicOff), "OFF"));
	optionMeniu->appendElement(new ma::TextButton(&buttonBrickTexture, font, new ma::Function([]() {std::ofstream f("score.txt"); f << 0; f.close(); highSchore = 0; }), "Reset score"));
	optionMeniu->appendElement(new ma::TextButton(&textButtonTexture, font, 0, "Sound:"));
	optionMeniu->appendElement(soundGroup);

	auto highScoreButton = new ma::TextButton(&textButtonTexture, font, nullptr, std::string(std::string("High Score ") + minute_sec(highSchore)).c_str());

	holder->appendElement(new ma::TextButton(&textButtonTexture, font, nullptr, "Stressed Out"));
	holder->appendElement(highScoreButton);
	holder->appendElement(new ma::TextButton(&buttonBrickTexture, font, new ma::Function(&play), "Play"));
	holder->appendElement(new ma::TextButton(&buttonBrickTexture, font, HowToPlay, "How to play..."));
	holder->appendElement(new ma::TextButton(&buttonBrickTexture, font, optionMeniu, "Options and settings...", 40));

	mainM.mainMenu = holder;

#pragma endregion

	while (window.isOpen())
	{
		

		deltaTime = GetTickCount() - time;
		time = GetTickCount();
		//deltaTime = 0.01;

		handleEvents(window);
		
		if(state == states::mainMenu)
		{
			window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

			highScoreButton->textContent.setString(std::string(std::string("High Score ") + minute_sec(highSchore)).c_str());

			if (!mainM.update(mouseReleased)) 
			{
				window.close();
			}
			window.display();
			window.clear();

		}else if(state == states::game)
		{
			//handle key

			sf::Vector2i deplasation = { 0,0 };

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				deplasation.x += 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				deplasation.x -= 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				deplasation.y -= 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				deplasation.y += 1;
			}

			if (deplasation.x != 0 && deplasation.y != 0)
			{
				mos.setPosition({ mos.getPosition().x + (int)(deplasation.x * deltaTime * mos.speed / (float)sqrt(2)), mos.getPosition().y + (int)(deplasation.y * deltaTime * mos.speed / (float)sqrt(2)) });
			}
			else
			{
				mos.setPosition({ mos.getPosition().x + (int)(deplasation.x * deltaTime * mos.speed), mos.getPosition().y + (int)(deplasation.y * deltaTime * mos.speed) });
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


			if (GetTickCount() > pillTime)
			{
				if (pillExists)
				{
					pillExists = 0;
					pillTime = GetTickCount() + rand() % 10000 + 15000;
				}
				else
				{
					pillExists = 1;
					pillTime = GetTickCount() + rand() % 10000 + 5000;
				}
			}

			if (pillExists)
			{
				if (colides(&mos, &pill))
				{
					pillExists = 0;
					pillTime = GetTickCount() + rand() % 10000 + 15000;
					stressValue += PillSP();
				}


				pill.calculatePadding(GetTickCount());
				pill.draw(&window, deltaTime);


			}

			if (GetTickCount() > clubTime)
			{
				if (clubExists)
				{
					clubTime = GetTickCount() + rand() % 8000 + 8000;
					clubExists = 0;
				}
				else
				{
					clubTime = GetTickCount() + rand() % 8000 + 8000;
					clubExists = 1;
					int count = sizeof(clubPositions) / sizeof(clubPositions[0]);
					int r = rand() % count;
					club.setPosition(clubPositions[r]);
				}
			}

			if (clubExists)
			{
				if (colides(&mos, &club))
				{
					clubExists = 0;
					clubTime = GetTickCount() + rand() % 9000 + 5000;
					currentItem = items::club;
				}



				club.calculatePadding(GetTickCount());
				club.draw(&window, deltaTime);
			}

			if(GetTickCount() > flowerTime)
			{
				if(flowerExists)
				{
					flowerTime = GetTickCount() + rand() % 16000 + 10000;
					flowerExists = 0;
				}else
				{
					flowerTime = GetTickCount() + rand() % 10000 + 10000;
					flowerExists = 1;
					int count = sizeof(flowerPositions) / sizeof(flowerPositions[0]);
					int r = rand() % count;
					flower.setPosition(flowerPositions[r]);
				}
			
			
			}

			if(flowerExists)
			{
				if(colides(&mos, &flower))
				{
					flowerExists = 0;
					flowerTime = flowerTime = GetTickCount() + rand() % 18000 + 10000;
					currentItem = items::flower;
				}

				flower.calculatePadding(GetTickCount());
				flower.draw(&window, deltaTime);
			
			}
			



			if (GetTickCount() > ballTime)
			{
				if (ballExists)
				{
					ballExists = 0;
					ballTime = GetTickCount() + rand() % 20000 + 15000;
				}
				else
				{
					ballExists = 1;
					ballTime = GetTickCount() + rand() % 80000 + 8000;
				}

			}

			if (ballExists)
			{
				ball.draw(&window, deltaTime);

				if (currentItem == items::fork)
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

			if(GetTickCount() > forkTime)
			{
				forkExists = 1;				
			}

			if(forkExists)
			{
				if (colides(&mos, &fork))
				{
					currentItem = items::fork;
					forkTime = GetTickCount() + rand() % 7000 + 7000;
					forkExists = 0;
				}else
				{
					fork.calculatePadding(GetTickCount());
					fork.draw(&window, deltaTime);
				}

				
			}
			



			for (int i = 0; i < sizeof(money) / sizeof(Item); i++)
			{
				if (GetTickCount() > moneyTime[i])
				{
					if (moneyExists[i])
					{
						moneyExists[i] = 0;
						moneyTime[i] = GetTickCount() + rand() % 25000 + 15000;
					}
					else
					{
						moneyExists[i] = 1;
						moneyTime[i] = GetTickCount() + rand() % 10000 + 10000;
					}
				}

				if (moneyExists[i])
				{
					if (colides(&mos, &money[i]))
					{
						moneyExists[i] = 0;
						moneyTime[i] = GetTickCount() + rand() % 20000 + 8000;
						moneyValue += MoneySP();
					}

					
					money[i].calculatePadding(GetTickCount());
					money[i].draw(&window, deltaTime);


				}
			}




#pragma region Collector

			if (GetTickCount() > collectorTime)
			{
				if (collectorActive)
				{

				}
				else
				{

					colector.setPosition(sf::Vector2i(80 * (MAPLENGTH - 2), rand() % 1000 + 10));
					collectorMoveTime = rand() % 2000 + 1000;
					collectorDirection = { -1, 0 };
					collectorActive = 1;
				}
			}

			if (collectorActive)
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

			if (colector.position.y < -70 || colector.position.y >(MAPHEIGHT - 1) * 80 || colector.position.x > MAPLENGTH * 80)
			{
				collectorActive = 0;
				collectorTime = GetTickCount() + rand() % 21000 + 12000;
				colector.setPosition(sf::Vector2i((MAPLENGTH - 7) * 80, (rand() % (80 * 5)) + (80 * 2)));
			}

			if (collectorActive)
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

			if (copil.getPosition().x >= (GARDENSTART - 1) * 80)
			{
				if (copilDIrection.x == 1)
				{
					copilDIrection.x = -1;
				}
			}

			if (colides(&mos, &copil))
			{
				stressValue += ChildSPS();
			}


			if (postasExists)
			{
				if (postasMoves)
				{
					postas.autoMove({ 0,1 }, deltaTime);
				}

				if (GetTickCount() > postasMoveTime)
				{
					postasMoveTime = GetTickCount() + rand() % 4000;
					if (postasMoves)
					{
						postasMoves = 0;
					}
					else
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

			}
			else if (GetTickCount() > postasTime)
			{
				postasExists = 1;
			}

			if (postas.getPosition().y > MAPHEIGHT * 80 + 20)
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

			if (GetTickCount() > grafferTime)
			{
				grafferTime = GetTickCount() + rand() % 12000 + 10000;
				if (!graferExists)
				{
					graferExists = 1;
					graferRetreating = 0;
				}
				else
				{
					graferRetreating = 1;
					int r = rand() % 2;
					if (r == 0)
					{
						graferRetreatingDirection = { 1, -1 };
					}
					else
					{
						graferRetreatingDirection = { 1, 1 };
					}
				}
			}

			if (graferExists)
			{

				if (!graferRetreating)
				{
					stressValue += GrafferSPS() * deltaTime;
				}


				if (colides(&mos, &grafer))
				{
					if (currentItem == items::club && !graferRetreating)
					{
						graferRetreating = 1;
						//grafferChangeDirectionTime = GetTickCount();
						grafferTime = GetTickCount();
						currentItem = 0;
						stressValue += GrafferBeatSP();
					}
				}



				if (graferRetreating)
				{
					grafer.autoMove(graferRetreatingDirection, deltaTime);
					grafer.speed = 0.50f;
				}
				else
				{
					grafer.speed = 0.20f;

					if (grafer.getPosition().x > (GARDENSTART + 5) * 80)
					{
						graferAttackingDirection.x = -1;
					}

					if (grafer.getPosition().x < (GARDENSTART - 1) * 80)
					{
						graferAttackingDirection.x = 1;
						grafer.autoMove(graferAttackingDirection, deltaTime);
					}
					else
						if (abs(mos.getPosition().x - grafer.getPosition().x) > 80 * 3)
						{
							//graferAttackingDirection.x = -1;
							grafer.autoMove(graferAttackingDirection, deltaTime);
						}
						else
						{
							//graferAttackingDirection.x = 1;
							grafer.autoMove(graferAttackingDirection, deltaTime);
						}

				}

				if (GetTickCount() > grafferChangeDirectionTime)
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

					}
					else
					{
						graferAttackingDirection.y = 0;
					}
				}

				if (!graferRetreating)
				{
					fixCollisionWall(grafer);
				}
				else
					if (grafer.position.y < -70 || grafer.position.y >(MAPHEIGHT - 1) * 80 || grafer.position.x > MAPLENGTH * 80)
					{
						graferExists = 0;
						grafferTime = GetTickCount() + rand() % 15000 + 6000;
						grafer.setPosition(sf::Vector2i((MAPLENGTH - 2) * 80, (rand() % (80 * 5)) + (80 * 2)));
					}

				if (graferExists)
				{
					fixCollision(grafer);
					grafer.draw(&window, deltaTime);
				}

			}




#pragma endregion

			moneyValue += moneySPS() * deltaTime;



#pragma region Fantoma
			//fantoma

			if(colides(&fantoma, &mos) && currentItem == items::flower)
			{
				currentItem = 0;
				fantomaTime = (rand() % 25000) + 15000 + GetTickCount();
				fantomaAwake = 0;
			}


			if (GetTickCount() > fantomaTime)
			{
				
				if (fantomaAwake)
				{
					fantomaTime = (rand() % 15000) + 10000 + GetTickCount();
					fantomaAwake = 0;
				}
				else
				{
					fantomaTime = (rand() % 25000) + 25000 + GetTickCount();
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

				if (fantoma.getPosition().x >= (GARDENSTART - 1) * 80)
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
			if (stressValue <= 0) 
			{	
				stressValue = 0; state = states::mainMenu; timebCount = clock() / 1000; 

				if(highSchore < timebCount - timeaCount)
				{
					highSchore = timebCount - timeaCount;
				}
			}
			
			float converted = 100 - stressValue;
			stressBar.value = &converted;
			stressBar.padding = { (int)view.getCenter().x - screenWith / 2, (int)view.getCenter().y - screenHeight / 2 };
			stressBar.draw(&window);


			moneyBar.padding = { (int)view.getCenter().x - screenWith / 2, (int)view.getCenter().y - screenHeight / 2 };
			moneyBar.draw(&window);

			timebCount = clock() / 1000;
			ceasText.setString(minute_sec(timebCount - timeaCount));
			ceasText.setPosition((int)view.getCenter().x - ceasText.getLocalBounds().width / 2, (int)view.getCenter().y - screenHeight / 2 + 50);
			window.draw(ceasText);

			setTextureRect(currentItemSprite, currentItem, 0);
			currentItemSprite.setPosition(sf::Vector2f{ (float)view.getCenter().x - screenWith / 2 + (screenWith - 560) , (float)view.getCenter().y - screenHeight / 2 + screenHeight - 90 });
			window.draw(currentItemSprite);

			window.display();

			//std::cout << colector.getPosition().x / 80 << " " << colector.getPosition().y /80 << " "<< mos.getPosition().x /80 <<" " << mos.getPosition().y/80 <<" " << collectorActive <<"\n";

			window.clear();
		
		}


	
	}

	return 0;
}