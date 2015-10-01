/**
@file Block.h
*/

#ifndef BLOCK_H
#define BLOCK_H

#include "Collidable.h"

/*! \class Block
	\Block class for the level
*/
class Block: public Collidable
{
	friend class Movable;
private:
	int blockHits; //!< blocks "life"
	bool blockUsed; //!< checking if power up blocks have been used
	bool special; //!< bool if the block releases powerups
	enum BlockType{floorBlock, normalBlock, breakableBlock, powerupBlock, usedBlock, invisBlock}; //!< enum for special objects

public:
	Block(); //!< default constructor
	
	void setBlock(int n, float xPos, float yPos, sf::Texture &t); //!< set type of block
	void setSpecial(bool s); //!< set if block is special
	void setHits(int h); //!< set amounts of hits a destroyable block can take
	void setUsed(bool u); //!< set if the block has been hit or not

	int getHits(); //!< return amount of hits left on a block
	bool getSpecial(); //!< return if the block is special or not
	bool getUsed(); //!< returns if the special block has been hit by player or not
};

#endif


