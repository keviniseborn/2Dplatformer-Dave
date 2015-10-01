/**
@file Npc.h
*/

#ifndef NPC_H
#define NPC_H

#include "Collidable.h"
/*! \class Npc
	\Class for non playable characters and powerups
	\Counting powerup to be an NPC as it moves as well.
*/

class Npc: public Collidable
{
protected:
	enum npcType{Goomba,koopa}; //!< NPC types
	enum powerUpType{shroom, star}; //!< Power Up types
	sf::Texture GoombaText, koopaLeftText, koopaRightText; //!< enemy textures
	sf::Texture shroomText, starText; //!< Power up textures
	bool direction; //!< direction (left == false, right == true);
	int powerUpNum; //!< number to check if npc is a power up, 0 = no power up, 1 = shroom, 2 = star

public:
	Npc();
	void randEnemy();			//!< Create a random enemy
	void randPowerUp(sf::Texture &t);//!< Create a random power up
	bool getDirection();		//!< Get the direction the NPC is facing
	int getPowerUPNum();

};
#endif