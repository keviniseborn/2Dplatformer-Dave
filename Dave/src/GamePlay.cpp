/**
@file GamePlay.cpp
*/


/*

That one block that doesn't seem to work....
Position correction seems weird

*/
#include "GamePlay.h"
#include <iostream>

void screenMovement(Movable &p, sf::View &v, sf::Sprite &s);

GamePlay::GamePlay()
{

}

void GamePlay::init()
{
	starText.loadFromFile("assets/graphics/star.png");
	shroomText.loadFromFile("assets/graphics/shroom.png");

	//! set the variable inPlay to be true
	inPlay = true;
	if(level != 1 && level != 2)
	{
		level =1;
	}
	//! Set the required variables for player
	player.setPos(Vector2D(450.f,460.f));
	player.setPlayable(true);

	//! load level function to load all the blocks
	floorTexture.loadFromFile("assets/graphics/block_floor.png");
	normalTexture.loadFromFile("assets/graphics/block_normal.png");
	breakTexture.loadFromFile("assets/graphics/block_breakable.png");
	powerUpTexture.loadFromFile("assets/graphics/block_powerup.png");
	usedBlockTexture.loadFromFile("assets/graphics/block_used.png");
	loadLevel("levelOne.txt");

	//! Create the enemy NPC's and push them back onto the npc vector
	if(level ==1)
	{
		npcHolder.randEnemy();
		npcHolder.setPos(Vector2D(-50.f, -50.f));
		npc.push_back(npcHolder);
		npcHolder.randEnemy();
		npcHolder.setPos(Vector2D(1180.f, 475.f));
		npc.push_back(npcHolder);
		npcHolder.randEnemy();
		npcHolder.setPos(Vector2D(790.f, 475.f));
		npc.push_back(npcHolder);
		npcHolder.randEnemy();
		npcHolder.setPos(Vector2D(950.f, 110.f));
		npc.push_back(npcHolder);
	}
	
	//! set the NPC's velocity and playability
	std::vector<Npc>::iterator npcMove;
	for(npcMove = npc.begin(); npcMove!= npc.end(); ++npcMove)
	{
		npcMove->setVel(Vector2D(-30.f, 0.f));
		npcMove->setAcc(Vector2D(0.0f, 5.f));
		npcMove->setPlayable(false);
	}
	
	//! load background and finish-point castle
	backgroundText.loadFromFile("assets/graphics/mario_background.png");
	backgroundSprite.setTexture(backgroundText);
	castleTexture.loadFromFile("assets/graphics/castle.png");
	castleSprite.setTexture(castleTexture);
	castleSprite.setPosition(2100,350);

	//!Set the main view properties
	mainView.setCenter(player.getPos().getX(), player.getPos().getY() - 150);
	mainView.setSize(800.f,600.f);
	mainView.setViewport(sf::FloatRect(0.f,0.f,1.f,1.f));
	mainView.zoom(0.75f);

	//!initialise the messages
	StringMessage[Title] = "Dave The Plumber!";
	StringMessage[Lives] = "Lives: ";
	StringMessage[Score] = "Score: ";
	StringMessage[TimeScore] = "Time-Score: ";
	StringMessage[FinalScore] ="Press R to play again! Final Score: ";

	//!load font for text
	SMFont.loadFromFile("assets/fonts/SMB.ttf");

	//!set font, character size and assign the message string to the variable
	for(int i = 0; i<5; ++i)
	{
		message[i].setFont(SMFont); //set font
		message[i].setCharacterSize(18); //set character size
		message[i].setString(StringMessage[i]); //set a string to the message array
	}
	//! position each message on the screen
	message[0].setCharacterSize(24); //set character size
	message[0].setPosition(250,300);
	message[1].setPosition(650,5);
	message[2].setPosition(20,5);
	message[3].setPosition(20,30);
	message[4].setPosition(-200,1000);

	//! Initialise the sound variables
	
	//!Background music
	backgroundMusic.openFromFile("assets/audio/main-theme.wav");
	backgroundMusic.play();
	backgroundMusic.setLoop(true);
	//! Win Sound

	//! Game Over Sound
	gameOverBuffer.loadFromFile("assets/audio/smb_gameover.wav");
	gameOverSound.setBuffer(gameOverBuffer);
	//! Coin Sound
	coinBuffer.loadFromFile("assets/audio/smb_coin.wav");
	coinSound.setBuffer(coinBuffer);
	//! Block Breaking Sound
	blockBreakBuffer.loadFromFile("assets/audio/smb_breakblock.wav");
	blockBreakSound.setBuffer(blockBreakBuffer);
	//! Power Up Block Sound
	powerUpBlockBuffer.loadFromFile("assets/audio/smb_fireworks.wav");
	powerUpBlockSound.setBuffer(powerUpBlockBuffer);
	//! Power Up Sound
	blockBreakBuffer.loadFromFile("assets/audio/smb_powerup.wav");
	blockBreakSound.setBuffer(blockBreakBuffer);
	

	//! assign remaining game play 
	numberOfNpc = 3;
	lives = 3;
	score = 0;
	timeScore = 3000;
	finalScore = 0;

}

void GamePlay::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	//draw objects

	target.draw(backgroundSprite);
	target.setView(titleView);
	target.setView(mainView);
	target.draw(castleSprite);
	target.draw(player);
	
	std::vector<std::vector<Block>>::const_iterator it;
	std::vector<Block>::const_iterator it2;
	for(it = blocks.begin(); it != blocks.end(); ++it)
	{
		for(it2 = it->begin(); it2 != it->end(); ++it2)
		{
			target.draw(*it2);
		}
	}
	
	std::vector<Npc>::const_iterator npcDraw;
	for(npcDraw = npc.begin(); npcDraw != npc.end(); ++npcDraw)
	{
		target.draw(*npcDraw);
	}

	std::vector<Npc>::const_iterator powerUpDraw;
	for(powerUpDraw = powerUps.begin(); powerUpDraw != powerUps.end(); ++powerUpDraw)
	{
		target.draw(*powerUpDraw);
	}
	
	for(int i=0; i<5; ++i)
	{
		target.draw(message[i]);
	}

}

void GamePlay::update(float time)
{
	//! Decrease the time bonus score over time
	if(inPlay == true && timeScore != 0)
	{
		timeScore = timeScore - time;
	}

	//!npc update functions
	std::vector<Npc>::iterator updateit;
	for(updateit = npc.begin(); updateit != npc.end(); ++updateit)
	{
		updateit->animate(); //!< animate the npc
		updateit->integrate(time); //!< integrate the npc
	}

	std::vector<Npc>::iterator powerUpdate;
	for(powerUpdate = powerUps.begin(); powerUpdate != powerUps.end(); ++powerUpdate)
	{
		powerUpdate->animate();
		powerUpdate->integrate(time);
	}

	//!integrate / animate player object
	player.animate();
	player.integrate(time);
	if(inPlay == true)player.handleInput(); //!< if game is inplay then the player can move
	
	collisionHandling();//!< collision handling function call
	screenMovement(player, mainView, backgroundSprite); //!< screen movement function call

	//! update the score messages with the actual score
	for(int i=0; i<5; ++i)
	{
		message[i].setString(StringMessage[i]);
		StringMessage[Lives] = "Lives: "+std::to_string(lives);
		StringMessage[Score] = "Score: " +std::to_string(score);
		StringMessage[TimeScore] = "Time-Score: "+ std::to_string(timeScore);
		StringMessage[FinalScore] = "Press R to play again! Final Score: "+ std::to_string(finalScore);
	}

	//! if player is dead, erase all npc's and run the init function again
	if(lives ==0)
	{
		backgroundMusic.stop();
		gameOverSound.play();
		_sleep(3000);
		npc.erase (npc.begin(),npc.end());
		init();
	}

	//! level finish function call (checks if level has been complete)
	levelFinish(time);
}

void GamePlay::screenMovement(Player &p, sf::View &v, sf::Sprite &s) //!< screen movement function to keep in track with player
{
	//!screen move right
	if(p.getPos().getX() > v.getCenter().x + 40)v.move(2.75f,0.f);
	if(p.getPos().getX() > v.getCenter().x + 40 && p.getBuff() == 1)v.move(4.f,0.f);
	//!screen move left
	if(p.getPos().getX() < v.getCenter().x - 40)v.move(-2.75f,0.f);
	if(p.getPos().getX() < v.getCenter().x - 40  && p.getBuff() == 1)v.move(-4.f,0.f);
	//!screen move up
	if(p.getPos().getY() < v.getCenter().y + 110)v.move(0.f,-5.f);
	//!screen move down
	if(p.getPos().getY() > v.getCenter().y + 120) v.move(0.f,5.f);

	//!keeps background static
	s.setPosition(v.getCenter().x-400.f ,v.getCenter().y -300.f);

	//!keeps messages in place
	message[1].setPosition(v.getCenter().x-295.f ,v.getCenter().y -225.f);
	message[2].setPosition(v.getCenter().x+175.f ,v.getCenter().y -225.f);
	message[3].setPosition(v.getCenter().x+120.f ,v.getCenter().y -200.f);
}

void GamePlay::collisionHandling()
{

	//!Collision between npcs and player
	std::vector<Npc>::iterator npcit;
	int counter;
	counter = 0;
	if(numberOfNpc != 0) //!< if npc's still exist
	{
		for(npcit = npc.begin(); npcit != npc.end();)
		{
			if(collision.AABBvsAABB(player, *npcit)) //!< if there is a collision between player and the npc
			{
				collision.collisionNormal(player,*npcit); //!< calculate collision normal
				if(npcit->getPowerUPNum() == 0) //!< if the NPC is an enemy
				{
					if(player.getNormal().getY() == -1)//!< if player lands on top of npc
					{
						collision.resolve(player, *npcit); //!< resolve collision
					}else{
						lives = lives-1; //!< reduce lives by 1
						player.setBuff(1, false); //!< remove player buffs
						player.setBuff(2, false); //!< remove player buffs
						backgroundMusic.setPitch(1.f); //!< change pitch of music back
						player.setPos(Vector2D(370.f,480.f)); //!< reset position of player
						mainView.setCenter(player.getPos().getX(), player.getPos().getY() - 150); //!< set screen center on player
					}
					if(npcit->getNormal().getY() == 1 && npcit->getPowerUPNum() != 1) //!< if the npc's normal is 1
					{
						player.setVel(Vector2D(player.getVel().getX(), -30.f)); //!< make player bounce a little bit
						npcit = npc.erase(npc.begin() + counter); //!< erase npc from vector
						score += 50; //!< increase score by 50
						--numberOfNpc;
					}else{
						++npcit;
					}
				}
				if(npcit->getPowerUPNum() == 1) //!< if the NPC is a shroom
				{
					npcit = npc.erase(npc.begin() + counter);
					score += 50;
					--numberOfNpc;
					coinSound.play();
					backgroundMusic.setPitch(1.3f);
					player.setBuff(1, true);
					
				}
			
			}
			else {++npcit;}
		
			++counter;
		}
	}
	//! if the player falls down
	if(player.getPos().getY() > 500) 
	{
		lives = lives-1; //!< reduce lives by 1
		player.setPos(Vector2D(370.f,460.f)); //!< reset players position
		mainView.setCenter(player.getPos().getX(), player.getPos().getY() - 150); //!< set screen center on player
		player.setBuff(1, false); //!< remove player buffs
		player.setBuff(2, false); //!< remove player buffs
		backgroundMusic.setPitch(1.f); //!< change pitch of music back
	}

	//collision between level and player
	std::vector<Block>::iterator it2;
	std::vector<std::vector<Block>>::iterator it;
	for(it = blocks.begin(); it != blocks.end();++it)
	{
		for(it2 = it->begin(); it2 != it->end();)
		{
			if(collision.AABBvsAABB(player,*it2) == true) //!< If player has collided with a block
			{
					collision.collisionNormal(player, *it2); //!< calculate the collision normal
					collision.resolve(player, *it2);		//!< resolve the collision
					if(it2->getNormal().getY() == -1 && it2->getDestroyable() == true) //!< if the player bounced ontop and the block is destroyable
					{
						if(it2->getHits() == 0) //!< and the blocks hits left is 0
						{
							it2 = it->erase(it2); //!< erase  block
							score = score + 25; //!< grand 25 score
							blockBreakSound.play();
						}else{
							score = score + 25;
							coinSound.play();
							it2->setHits(it2->getHits()-1); //!< else reduce hits by 1
						}
					}
					if(it2->getNormal().getY() == -1 && it2->getSpecial() == true) //!< if player hits from underneat on a special block
					{
						if(it2->getHits() != 0)
						{
						
							it2->setBlock(5, it2->getPos().getX(), it2->getPos().getY(), usedBlockTexture); //!< change block to be used
							score = score + 25; //!< increase score
							powerUpBlockSound.play();
							Npc tempPowerUP;
							tempPowerUP.randPowerUp(shroomText);
							tempPowerUP.setPos(Vector2D(it2->getPos().getX() + 10, it2->getPos().getY() - 30));
							numberOfNpc += 1;
							npc.push_back(tempPowerUP);
							it2->setHits(0); //!< set hits left to 0
						}
					}
			}else{++it2;}
		}
	}
	
	std::vector<Npc>::iterator npcit2;
	std::vector<Block>::iterator it4;
	std::vector<std::vector<Block>>::iterator it3;
	//collision between level and npcs
	for(it3 = blocks.begin(); it3 != blocks.end();++it3)
	{
		for(it4 = it3->begin(); it4 != it3->end(); ++it4)
		{
			for(npcit2 = npc.begin(); npcit2 != npc.end();)
			{
				if(collision.AABBvsAABB(*npcit2, *it4)) //!< if there is a collision between an npc and a block
				{
					collision.collisionNormal(*npcit2, *it4); //!< calculate collision normal
					collision.resolve(*npcit2, *it4);		//!< resolve the collision
				
					//! depending on which side the npc hits, change it's velocity
					if(npcit2->getNormal().getX() == 1)
					{
						npcit2->setVel(Vector2D(30.f,0.f));
					}
					if(npcit2->getNormal().getX() == -1)
					{
						npcit2->setVel(Vector2D(-30.f,0.f));
					}
					if(npcit2->getNormal().getX() == 0)
					{
						npcit2->setVel(Vector2D(-30.f,0.f));
					}
					if(npcit2->getPowerUPNum() == 1 || npcit2->getPowerUPNum() == 2)
					{
						npcit2->setVel(Vector2D(30.f,0.f));
						npcit2->setAcc(Vector2D(0.f,5.f));
					}
				
				}else{++npcit2;}
			}
		}
	}
}


void GamePlay::levelFinish(float time) //!< level finish function
{


	if(inPlay == false) //!< if game is not inplay
	{
			finalScore = score + timeScore; //!< calculate final score
			finalScore = finalScore + (lives*50); //!<include remaining lives in score
			StringMessage[FinalScore] = "Press R to play again! Final Score: "+ std::to_string(finalScore); //!<update final score
			backgroundMusic.stop();
			gameOverSound.play();
	}
	if(player.getPos().getX() >= 2120 && level == 1 && inPlay == true) //!< if the player reaches the end
	{
	
		player.setVel(Vector2D(0.f,0.f)); //!< stop the player from moving
		_sleep(20);
		blocks.erase(blocks.begin(), blocks.end());
		loadLevel("levelTwo.txt");
		level = 2;
		npc.erase (npc.begin(),npc.end()); //!< erase the npc vector
		castleSprite.setPosition(2470.f, 320.f);
		player.setPos(Vector2D(450.f,460.f));
		mainView.setCenter(player.getPos().getX(), player.getPos().getY() - 150);

	}

	if(player.getPos().getX() >=2470 && level == 2 && inPlay == true)
	{
		message[4].setPosition(2250,250); //!< set position of message in correct location
		npc.erase (npc.begin(),npc.end()); //!< erase the npc vector
		inPlay = false;
		level = 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && inPlay == false) //!< if the player hits R
		{
			blocks.erase(blocks.begin(), blocks.end());
			inPlay = true; // change inplay to be true
			init();			// re initialise the game
		}
	
	if(lives == 0)
	{
		level = 1;
		message[4].setPosition(mainView.getCenter().x,250); //!< set position of message in correct location
		backgroundMusic.stop();
		gameOverSound.play();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //!< if the player hits R
		{
			inPlay = true; //!< change inplay to be true
			npc.erase (npc.begin(),npc.end()); //!< erase the npc vector
			init();			//!< re initialise the game
		}
	}
}


void GamePlay::loadLevel(char * filename) //!< level loading function
{
	std::ifstream levelFile;
	std::istringstream ss;
	std::string currentLine;
	int currentNum;
	levelFile.open(filename);

	//! set variables to be 0
	int levelHeight = 0; 
	int levelWidth = 0;
	float blockSize = 0;

	if(levelFile.is_open())
	{
	//Get level info
		getline(levelFile, currentLine); //gets the first line of the file
		ss.str(currentLine);
		ss >> levelHeight;
		ss >> levelWidth;
		ss >> blockSize;

		numberOfBlocks = levelWidth * levelHeight;
	//resize the layout
		layout.resize(levelHeight);
		for(int i=0; i<levelHeight; ++i)
		{
			layout[i].resize(levelWidth);
		}
	
	//get block info
		int lineNumber = 0;
		
		
		while(getline(levelFile, currentLine))
		{
			int rowNumber = 0;
			ss.clear();
			ss.str(currentLine);

			while (ss >> currentNum)
			{
				
				layout[rowNumber][lineNumber] = currentNum;
				++rowNumber;

			}

			lineNumber++;
		}
		levelFile.close();
	}	


	//implementing each sprite into the vector of blockSprites
	std::vector<std::vector<int>>::iterator it;
	std::vector<int>::iterator it2;
	
	std::vector<Block> rowVector; //!< vector for pushing into the 2d Vector "blocks"
	int row, col; //!< rows and cols
	Block currentBlock; //!< current block to push into the row vector

	row = 0;
	for(it = layout.begin(); it != layout.end(); ++it)
	{
		rowVector.clear();
		col = 0;
		for(it2 = it->begin(); it2 != it->end(); ++it2)
		{
			if(*it2 == 1)
			{
				currentBlock.setBlock(1, row* blockSize, col*blockSize, floorTexture);
				currentBlock.setPos(Vector2D(row* blockSize, col*blockSize));
				rowVector.push_back(currentBlock);
	
			}

			if(*it2 == 2)
			{
				
				currentBlock.setBlock(2, row* blockSize, col*blockSize, normalTexture);
				currentBlock.setPos(Vector2D(row* blockSize, col*blockSize));
				rowVector.push_back(currentBlock);
		
			}
			
			if(*it2 == 3)
			{
				currentBlock.setBlock(3, row* blockSize, col*blockSize, floorTexture);

				currentBlock.setPos(Vector2D(row* blockSize, col*blockSize));
				rowVector.push_back(currentBlock);
			}

			if(*it2 == 4)
			{
				currentBlock.setBlock(4, row* blockSize, col*blockSize, breakTexture);

				currentBlock.setPos(Vector2D(row* blockSize, col*blockSize));
				rowVector.push_back(currentBlock);
			}

			if(*it2 == 5)
			{
				currentBlock.setBlock(5, row* blockSize, col*blockSize, powerUpTexture);

				currentBlock.setPos(Vector2D(row* blockSize, col*blockSize));
				rowVector.push_back(currentBlock);
			}

			++col;
		}
		blocks.push_back(rowVector);
		++row;
	}


}