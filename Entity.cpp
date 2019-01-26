#include "Entity.h"

extern unsigned char map[MAPLENGTH][MAPHEIGHT];

int deltax;
int deltay;
int intersectx;
int intersecty;

void fixCollision(Entity &entity)
{

	if (entity.lastpos.x < entity.position.x) { entity.movingright = 1; }
	else { if (entity.lastpos.x > entity.position.x)entity.movingright = 0; }
	if (entity.lastpos.y < entity.position.y) { entity.movingdown = 1; }
	else { entity.movingdown = 0; }

	if (entity.movingdown)
	{

		for (int y = 0; y < MAPHEIGHT; y++)
		{




			if (entity.movingright)
			{
				for (int x = 0; x < MAPLENGTH; x++)
				{
					if (map[x][y] >= tiles::brickWall)
					{

						deltax = x * 80 + 40 - entity.getcenterx();
						deltay = y * 80 + 40 - entity.getcentery();
						intersectx = abs(deltax) - (40 + entity.sizeofentity.x / 2);
						intersecty = abs(deltay) - (40 + entity.sizeofentity.y / 2);




						if (intersectx < 0.0f&&intersecty < 0.0f)
						{
							if (abs(intersectx) <= abs(intersecty))/// move on x
							{
								if (deltax < 0)
								{

									if (!entity.movingright) entity.position.x = x * 80 + 80;
									///stanga
								}
								else
								{

									if (entity.movingright)entity.position.x = x * 80 - entity.sizeofentity.x;   ///dreapta

								}



							}
							else
							{///move on y
								if (deltay < 0)
								{

									entity.position.y = y * 80 + 80;

								}
								else

								{
									entity.position.y = y * 80 - entity.sizeofentity.y;
								}


							}


						}
					}
				}
			}
			else
			{
				for (int x = MAPLENGTH; x >= 0; x--)
				{
					if (map[x][y] >= tiles::brickWall)
					{
						deltax = x * 80 + 40 - entity.getcenterx();
						deltay = y * 80 + 40 - entity.getcentery();
						intersectx = abs(deltax) - (40 + entity.sizeofentity.x / 2);
						intersecty = abs(deltay) - (40 + entity.sizeofentity.y / 2);



						if (intersectx < 0.0f&&intersecty < 0.0f)
						{
							if (abs(intersectx) <= abs(intersecty))/// move on x
							{
								if (deltax < 0)
								{

									if (!entity.movingright) entity.position.x = x * 80 + 80;
									///stanga
								}
								else
								{

									if (entity.movingright)entity.position.x = x * 80 - entity.sizeofentity.x;   ///dreapta

								}



							}
							else
							{///move on y
								if (deltay < 0)
								{

									entity.position.y = y * 80 + 80;

								}
								else

								{
									entity.position.y = y * 80 - entity.sizeofentity.y;
								}


							}


						}
					}

				}
			}

		}


	}
	else               /////////////////////////////////////moving up
	{
		for (int y = MAPHEIGHT; y >= 0; y--)
		{
			if (entity.movingright)
			{
				for (int x = 0; x < MAPLENGTH; x++)
				{
					if (map[x][y] >= tiles::brickWall)
					{
						deltax = x * 80 + 40 - entity.getcenterx();
						deltay = y * 80 + 40 - entity.getcentery();
						intersectx = abs(deltax) - (40 + entity.sizeofentity.x / 2);
						intersecty = abs(deltay) - (40 + entity.sizeofentity.y / 2);


						if (intersectx < 0.0f&&intersecty < 0.0f)
						{
							if (abs(intersectx) <= abs(intersecty))/// move on x
							{
								if (deltax < 0)
								{

									if (!entity.movingright) entity.position.x = x * 80 + 80;
									///stanga
								}
								else
								{

									if (entity.movingright)entity.position.x = x * 80 - entity.sizeofentity.x;   ///dreapta

								}



							}
							else
							{///move on y
								if (deltay < 0)
								{

									entity.position.y = y * 80 + 80;

								}
								else

								{
									entity.position.y = y * 80 - entity.sizeofentity.y;
								}


							}


						}
					}

				}
			}
			else
			{
				for (int x = MAPLENGTH; x >= 0; x--)
				{
					if (map[x][y] >= tiles::brickWall)
					{
						deltax = x * 80 + 40 - entity.getcenterx();
						deltay = y * 80 + 40 - entity.getcentery();
						intersectx = abs(deltax) - (40 + entity.sizeofentity.x / 2);
						intersecty = abs(deltay) - (40 + entity.sizeofentity.y / 2);



						if (intersectx < 0.0f&&intersecty < 0.0f)
						{						
							if (abs(intersectx) <= abs(intersecty))/// move on x
							{
								if (deltax < 0)
								{

									if (!entity.movingright) entity.position.x = x * 80 + 80;
									///stanga
								}
								else
								{

									if (entity.movingright)entity.position.x = x * 80 - entity.sizeofentity.x;   ///dreapta

								}



							}
							else
							{///move on y
								if (deltay < 0)
								{

									entity.position.y = y * 80 + 80;

								}
								else

								{
									entity.position.y = y * 80 - entity.sizeofentity.y;
								
								}


							}


						}
					}

				}
			}

		}
	}


	
		
}



void fixCollisionWall(Entity &entity)
{
	///fix player position
	if (entity.position.x < 0) { entity.position.x = 0; }
	if (entity.position.x + entity.sizeofentity.x > 80 * MAPLENGTH) { entity.position.x = 80 * MAPLENGTH - entity.sizeofentity.x; }
	if (entity.position.y < 0) { entity.position.y = 0; }
	if (entity.position.y + entity.sizeofentity.y > 80 * MAPHEIGHT) { entity.position.y = 80 * MAPHEIGHT - entity.sizeofentity.y; }



}

void updateMovement(Entity &entity)
{
	entity.lastpos.x = entity.position.x;
	entity.lastpos.y = entity.position.y;
}

bool colides(Entity * a, Entity * b)
{
	deltax = a->getcenterx() - b->getcenterx();
	deltay = a->getcentery() - b->getcentery();
	intersectx = abs(deltax) - (a->sizeofentity.x / 2 + b->sizeofentity.x / 2);
	intersecty = abs(deltay) - (a->sizeofentity.y / 2 + b->sizeofentity.y / 2);
	if(intersectx <= 0.f && intersecty <= 0.f)
	{
		return 1;
	}else
	{
		return 0;
	}
}

void Item::calculatePadding(float time)
{

	paddingPosition = sin(time / 200) * 20;

}

void Item::draw(sf::RenderWindow * window)
{
	sprite.setPosition({ (float)position.x, (float)position.y + paddingPosition });
	window->draw(sprite);

}
