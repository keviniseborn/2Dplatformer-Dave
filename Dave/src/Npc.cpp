#include "Npc.h"

Npc::Npc()
{
	//! load all the textures from files
	GoombaText.loadFromFile("assets/graphics/Goomba.png");
	koopaLeftText.loadFromFile("assets/graphics/koopa-left.png");
	koopaRightText.loadFromFile("assets/graphics/Koopa-right.png");
	//shroomText.loadFromFile("assets/graphics/shroom.png");
//	starText.loadFromFile("assets/graphics/star.png");

	//set basic properties of object
	iMass = 0.5;
	elasticity = 0.5;
	acceleration = Vector2D(0.f,  5.f);
}

void Npc::randEnemy() //!< creates a random enemy 
{
	int v1;
	v1 = rand() % 2;

	//! create Goomba 
	if(v1 == Goomba)
	{
		moveSprite.setTexture(GoombaText);
		moveSprite.setScale(0.8f, 0.8f);
		
		cols = 5;
		size.setX(GoombaText.getSize().x/cols);
		size.setY(GoombaText.getSize().y);
		setAnimateProperties(4, size.getY(), size.getX(), 0.3f);

		size.setX((GoombaText.getSize().x/cols)*0.8f);
		size.setY(GoombaText.getSize().y*0.8f);
		powerUpNum = 0;

	}
	//! create Koopa 
	if(v1 == koopa)
	{
		cols = 4;
		moveSprite.setTexture(koopaLeftText);
		moveSprite.setScale(0.8f, 0.8f);
		size.setX(koopaLeftText.getSize().x / cols);
		size.setY(koopaLeftText.getSize().y);
		setAnimateProperties(4, size.getY(), size.getX(), 0.3f);

		size.setX((koopaLeftText.getSize().x / cols) * 0.8f);
		size.setY(koopaLeftText.getSize().y* 0.8f);
		powerUpNum = 0;
	}

	//! set animation properties
	count = 0;
	lastTime = 0;
	tileWidth = imageWidth;

	r.left = 0;
	r.top = 0;
	r.width = tileWidth;
	r.height = imageHeight;

	direction = 0;
}

void Npc::randPowerUp(sf::Texture &t)
{
	int v1;
	v1 = 0;
	

	if(v1 == shroom)
	{
	
		cols = 1;
		moveSprite.setTexture(t);
		moveSprite.setScale(0.7f, 0.7f);	

		size.setX(t.getSize().x);
		size.setY(t.getSize().y);
		setAnimateProperties(cols, size.getY(), size.getX(), 1.f);

		size.setX((t.getSize().x)*0.7f);
		size.setY(t.getSize().y*0.7f);
		powerUpNum = 1;
	}

	if(v1 == star)
	{
		
		cols = 1;
		moveSprite.setTexture(t);
		moveSprite.setScale(0.7f, 0.7f);

		size.setX(t.getSize().x);
		size.setY(t.getSize().y);
		setAnimateProperties(cols, size.getY(), size.getX(), 1.f);

		size.setX((t.getSize().x)*0.7f);
		size.setY(t.getSize().y*0.7f);
		powerUpNum = 2;
	}
	
	//! set animation properties
	count = 0;
	lastTime = 0;
	tileWidth = imageWidth;

	r.left = 0;
	r.top = 0;
	r.width = tileWidth;
	r.height = imageHeight;
	
	direction = 0;
}

bool Npc::getDirection()
{
	return direction;
}

int Npc::getPowerUPNum()
{
	return powerUpNum;
}