#include "Block.h"

Block::Block()
{
}

void Block::setBlock(int n, float xPos, float yPos, sf::Texture &t) //!<set block function
{

	//!set image properties (all blocks same size)
	imageHeight = t.getSize().y;
	imageWidth = t.getSize().x;
	tileWidth = imageWidth;
	animationDelay =1;

	//! Checks value entered in function and creates a block depending on the integer value
	if(n == 1)
	{
		moveSprite.setTexture(t);
		moveSprite.setScale(0.6f, 0.6f);
		moveSprite.setPosition(xPos, yPos);
		blockHits = 1;
		special = false;
		destroyable = false;
		iMass = 0.f;
		elasticity = 0.01f;

		size.setX(t.getSize().x*0.6f);
		size.setY(t.getSize().y*0.6f);
	}

	if(n == 2)
	{
		moveSprite.setTexture(t);
		moveSprite.setScale(0.6f, 0.6f);
		moveSprite.setPosition(xPos, yPos);
		blockHits = 1;
		special = false;
		destroyable = false;
		iMass = 0.f;
		elasticity = 0.1f;

		size.setX(t.getSize().x*0.6f);
		size.setY(t.getSize().y*0.6f);
	}

	if(n == 3)
	{

		moveSprite.setScale(0.6f, 0.6f);
		blockHits = 1;
		special = false;
		destroyable = false;
		iMass = 0.f;
		elasticity = 0.1f;

		size.setX(t.getSize().x*0.6f);
		size.setY(t.getSize().y*0.6f);
	}

	if(n == 4)
	{
		moveSprite.setTexture(t);
		moveSprite.setScale(0.6f, 0.6f);
		moveSprite.setPosition(xPos, yPos);
		blockHits = 1;
		special = false;
		destroyable = true;
		iMass = 0.f;
		elasticity = 0.1f;

		size.setX(t.getSize().x*0.6f);
		size.setY(t.getSize().y*0.6f);
	}

	if(n == 5)
	{
		moveSprite.setTexture(t);
		moveSprite.setScale(0.6f, 0.6f);
		moveSprite.setPosition(xPos, yPos);
		blockHits = 1;
		special = true;
		destroyable = false;
		blockUsed = false;
		iMass = 0.f;
		elasticity = 0.1f;

		size.setX(t.getSize().x*0.6f);
		size.setY(t.getSize().y*0.6f);
	}
	
	if(n == 6)
	{
		moveSprite.setTexture(t);
		moveSprite.setScale(0.6f, 0.6f);
		moveSprite.setPosition(xPos, yPos);
		blockHits = 1;
		special = false;
		destroyable = false;
		blockUsed = true;
		iMass = 0.f;
		elasticity = 0.1f;

		size.setX(t.getSize().x*0.6f);
		size.setY(t.getSize().y*0.6f);
	}
}

void Block::setHits(int h) //!< set hits for block
{
	blockHits = h;
}

void Block::setSpecial(bool s) //!< set if the block is special
{
	special = s;
}

void Block::setUsed(bool u)  //!< set if the block has been hit
{
	blockUsed = u;
}

int Block::getHits() //!< getter for hits left on a block
{
	return blockHits;
}

bool Block::getSpecial() //!< getter for if the block is special
{
	return special;
}

bool Block::getUsed() //!< getter for if the block has been hit
{
	return blockUsed;
}