/**
@file Player.cpp
**/


#include "Player.h"

Player::Player()
{
	//! set players basic properties
	acceleration = Vector2D(0.f, 5.0f);
	iMass = 0.2;
	elasticity = 0.2;
	playable = true;
	shroomBuff = false;

	//! load textures from file
	leftText.loadFromFile("assets/graphics/Mario_left.png");
	rightText.loadFromFile("assets/graphics/Mario_right.png");
	jumpText.loadFromFile("assets/graphics/Mario_jump.png");
	stillText.loadFromFile("assets/graphics/Mario_still.png");
	crouchText.loadFromFile("assets/graphics/Mario_crouch.png");

	//! Load the sound for jumping
	soundbuffer.loadFromFile("assets/audio/smb_jump-small.wav");
	jumpSound.setBuffer(soundbuffer);

	//! set the sprites texture and scale
	moveSprite.setTexture(stillText);
	moveSprite.setScale(0.6f, 0.6f);
	cols = 1;

	//! set image height/width and size (for collision and animation)
	imageHeight = rightText.getSize().y;
	imageWidth = rightText.getSize().x / 3;
	size.setX(rightText.getSize().x / 3 * 0.6);
	size.setY(rightText.getSize().y * 0.6);

	//! more properties for animation
	animating = false;
	animationDelay = 0.3f;
	count = 0;
	lastTime = 0;
	tileWidth = imageWidth;

	r.left = 0;
	r.top = 0;
	r.width = tileWidth;
	r.height = imageHeight;
}


void Player::handleInput() //!< handles players input from keyboard
{
	/*!
	* Function handles all player input
	* Changes velocity on key-press
	* Changes the texture and animation properties depending on which key you press
	*/
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //!< if player pushes right
	{
		if(shroomBuff == true) velocity = Vector2D(100.0f, velocity.getY()); //!< change velocity
		if(shroomBuff == false) velocity = Vector2D(80.0f, velocity.getY()); //!< change velocity
		acceleration = Vector2D(0.f, 5.0f);			
		moveSprite.setTexture(rightText);				//!< set texture to be right
		setAnimateProperties(3, rightText.getSize().y , leftText.getSize().x / 3, 0.3); //!< set animate properties of new texture
		animating = true; //!< set animating to be true
	}


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(shroomBuff == true) velocity = Vector2D(-100.0f, velocity.getY());
		if(shroomBuff == false) velocity = Vector2D(-80.0f, velocity.getY());
		acceleration = Vector2D(0.f, 5.0f);
		moveSprite.setTexture(leftText);
		if(animating == false)
		{
			setAnimateProperties(3, leftText.getSize().y, leftText.getSize().x / 3, 0.3);
		}
		animating = true;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if(onBlock == true)
		{
			jumpSound.play();
			if(shroomBuff == true) velocity = Vector2D(velocity.getX(), -150.0f);
			if(shroomBuff == false) velocity = Vector2D(velocity.getX(), -120.0f);
			acceleration = Vector2D(0.f, 5.0f);
			moveSprite.setTexture(jumpText);
			setAnimateProperties(1, jumpText.getSize().y, jumpText.getSize().x, 0.3);
			onBlock = false;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity = Vector2D(velocity.getX(), velocity.getY());	
		acceleration = Vector2D(0.f, 5.0f);
		moveSprite.setTexture(crouchText);
		setAnimateProperties(1, crouchText.getSize().y, crouchText.getSize().x, 0.3);
	}else{
		acceleration = Vector2D(0.f, 5.0f);
	}
	if(sf::Keyboard::isKeyPressed == false)
	{
		animating = false;
	}
	
}

void Player::setBuff(int b, bool t)
{
	if(b==1) shroomBuff = t;
	if(b==2) starBuff = t;
}

int Player::getBuff()
{
	if(shroomBuff == false && starBuff == false) return 0;
	if(shroomBuff == true && starBuff == false)	return 1;
	if(shroomBuff == false && starBuff == true) return 2;
}
