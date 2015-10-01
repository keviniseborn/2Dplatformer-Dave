/**
@file Movable.h
*/

#ifndef MOVABLE_H
#define MOVABLE_H

#include <SFML/Graphics.hpp>
#include "Vector2D.h"
#include <iostream>

/*! \class Movable
	\Class for all the movable objects in the game
	\Contains position/velocity/acceleration etc.
*/

class Movable: public sf::Drawable

{
protected:
	//variables for movement
	Vector2D position;				//!< Vector2D of position
	Vector2D velocity;				//!< Vector2D of velocity
	Vector2D acceleration;			//!< Vector2D of acceleration
	Vector2D drag;					//!< Vector2D of drag
	Vector2D maxVelocity;			//!< Max velocity variable as a 2D Vector
	
	
	//sprite variables
	sf::Sprite moveSprite;			//!< sprite of movable object

	bool playable;					//!< Is object playable

	//animation variables
	sf::Clock animationClock;					//!< a clock shared by all animations
	int count;									//!< animation count
	double lastTime;							//<! previous time for animation 
	sf::IntRect r;								//!< texture rect for animation
	int cols;									//!< Columns for animation
	float imageHeight, imageWidth, tileWidth;	//!< stores texture height and width for animation
	float animationDelay;						//!< delay for animation sequence
	bool animating;								//!< check if object is currently in animation

public:
	Movable();											//!< default constructor
	void init(Vector2D &v, Vector2D& p, Vector2D &a);	//!< initialise function

	void setPos(Vector2D &pos);				//!< Position setter
	void setVel(Vector2D &vel);				//!< Velocity setter
	void setAcc(Vector2D &acc);				//!< Acceleration setter
	void scaleSprite(float sx, float sy);	//!< Scale sprite function
	void setPlayable(bool p);				//!< set playability of object

	Vector2D getPos();		//!< Position getter
	Vector2D getVel();		//!< Velocity getter
	Vector2D getAcc();		//!< Acceleration getter
	bool getPlayable();		//!< Getter for the playability bool
	int getCols();			//!< Getter for colums in sprite sheet
	float getImageHeight();	//!< Getter for images height
	float getImageWidth();	//!< Getter for images width
	float getAnimDelay();	//!< Getter for sprites animation delay

	void integrate(float h);													//!< Integrate function
	void setTexture(sf::Texture t, int columns, float animDelay);				//!< texture setter
	void animate();																//!< Animate function
	void setAnimateProperties(int columns, int height, int width, float delay);	//!< Animation properties setter function
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;	//!< Draw function for objects




};
#endif