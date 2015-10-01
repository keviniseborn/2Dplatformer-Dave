/**
@file GamePlay.h
*/

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Player.h"
#include "Npc.h"
#include "Block.h"
#include "Collision.h"


/*! \class GamePlay
	\handles the game play events
*/

class GamePlay: public sf::Drawable
{
protected:
	//!game play variables
	Player player; //!< player object
	Npc npcHolder; //!< holder for the npc object
	int numberOfNpc; //!< number of NPC's in the game
	bool inPlay; //!< if the game is currently in play
	std::vector<Npc> npc; //!< vector of NPC objects
	std::vector<Npc> powerUps; //!< Vector of Power UPs
	Collision collision; //!< Collision object
	unsigned int ScreenWidth, screenHeight; //!< screen width and screen height

	//! background and castle variables
	sf::Texture backgroundText;
	sf::Sprite backgroundSprite;
	sf::Texture castleTexture;
	sf::Sprite castleSprite;
	sf::Texture shroomText, starText;

	//! view variables
	sf::View mainView;
	sf::View titleView;
	sf::View scoreView;
	sf::View livesView;
	
	//! text variables
	sf::Font SMFont;
	sf::Text message[5];
	enum Messages {Title, Lives, Score, TimeScore, FinalScore};
	int score;
	int lives;
	int timeScore;
	int finalScore;
	int level; 
	std::string StringMessage[5];

	//! level loading variables 
	std::vector<std::vector<int>> layout;	//!< vector of ints for block layout
	std::vector<Block> rowVector;			//!< 1D vector of blocks to load into blocks vector
	std::vector<std::vector<Block>> blocks;	//!< 2D vector of blocks
	sf::Texture floorTexture, normalTexture, breakTexture, powerUpTexture, usedBlockTexture; //!< textures for special objects
	int numberOfBlocks;						//!< Number of blocks in the level
	float blockScale;						//!< scale of blocks

	//! Sound variables
	sf::SoundBuffer backgroundbuffer, gameOverBuffer, coinBuffer, winBuffer, blockBreakBuffer, powerUpBlockBuffer, powerUpBuffer;
	sf::Sound gameOverSound, coinSound, winSound, blockBreakSound, powerUpBlockSound, powerUpSound;
	sf::Music backgroundMusic;
public:
	//game play functions

	GamePlay();																	//!< constructor
	void init();																//!< initialise function
	void update(float time);													//!< Game update function
	void collisionHandling();													//!< Collision handling function
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;	//!< Draw function
	void screenMovement(Player &p, sf::View &v, sf::Sprite &s);				//!< function for screen views
	void levelFinish(float time);												//!< Level finish check function
	void loadLevel(char * filename);											//!< Level loading function

};

#endif