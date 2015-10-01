/**
@file Player.h
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Collidable.h"
#include <SFML/Audio.hpp>

/*! \class Player
	\
*/

class Player: public Collidable
{
protected:
	enum Direction{left,right,jump,still,crouch};					//!< player states
	sf::Texture leftText,rightText,jumpText,stillText,crouchText;	//!< different player textures
	bool playing;													//!< is player playing
	sf::SoundBuffer soundbuffer;									//!< buffer for jump sound
	sf::Sound jumpSound;											//!< jump sound
	bool starBuff, shroomBuff;										//!< if the player has a powerup

public:
	Player();				//!< default constructor

	void handleInput();		//!< function for handling the input of the player
	void setBuff(int b, bool t); //!< function to set the players buff - integer for which buff and bool on or off

	int getBuff();			//!< returns what type of buff player has - 0 = none, 1 = shroom, 2 = star
};
#endif