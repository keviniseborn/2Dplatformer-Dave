/**
@file Movable.cpp
**/

#include "Movable.h"

Movable::Movable()			//!< default constructor
{
}
void Movable::init(Vector2D &v, Vector2D& p, Vector2D &a) //!< initialise function
{
	velocity = v;
	position = p;
	acceleration = a;

}

void Movable::setPos(Vector2D &pos)		//!< Position setter
{
	position = pos;
}

void Movable::setVel(Vector2D &vel)		//!< Velocity setter
{
	velocity = vel;
}

void Movable::setAcc(Vector2D &acc)		//!< Acceleration setter
{
	acceleration = acc;
}

void Movable::scaleSprite(float sx, float sy)
{
	moveSprite.scale(sx,sy);
}

void Movable::setPlayable(bool p)
{
	playable = p;
}

Vector2D Movable::getPos()		//!< Position getter
{
	return position;
}

Vector2D Movable::getVel()		//!< Velocity getter
{
	return velocity;
}

Vector2D Movable::getAcc()		//!< Acceleration getter
{
	return acceleration;
}

bool Movable::getPlayable()
{
	return playable;
}

int Movable::getCols()		//!< Sprite sheet column getter
{
	return cols;
}

float Movable::getImageHeight() //!< Getter for images height
{
	return imageHeight;
}

float Movable::getImageWidth()	//!< Getter for images width
{
	return imageWidth;
}

float Movable::getAnimDelay()	//!< Getter for animation delay time
{
	return animationDelay;
}

void Movable::integrate(float h)		//!< Integrate function
{
	if(playable) //!< if the object is playable
	{
		drag.setX(velocity.getX() / 20); //!< calculate drage
	}else{
		drag.setX(0.f);
	}

	//! improved euler for movement
	Vector2D v2;
	velocity = velocity + (acceleration) -drag;
	v2 = velocity + (acceleration * h);

	position = position + (((velocity + v2) * h)/2);

	moveSprite.setPosition(position.getX(), position.getY());
}

void Movable::setTexture(sf::Texture t, int columns, float animDelay) //!< texture setter
{
	//!< sets texture rect, and all other required properties for animation
	moveSprite.setTexture(t);

	cols = columns;
	imageHeight = t.getSize().y;
	imageWidth = t.getSize().x / cols;
	tileWidth = imageWidth;

	r.left = 0;
	r.top = 0;
	r.width = tileWidth;
	r.height = imageHeight;

	moveSprite.setTextureRect(r);

	animationDelay = animDelay;
	

}

void Movable::animate()
{

	//Animation
		if(animationClock.getElapsedTime().asSeconds()-lastTime>animationDelay) 
		{
			lastTime=animationClock.getElapsedTime().asSeconds();

			++count;
			if(count==cols)
			{
				r.left=0;
				count =0;
			}
			else
			{
				r.left+=tileWidth;
			}
	
			moveSprite.setTextureRect(r);
		}
}

void Movable::setAnimateProperties(int columns, int height, int width, float delay)
{
	cols = columns;
	count = 0;
	r.left=0;
	r.top = 0;
	imageHeight = height;
	imageWidth = width;
	animationDelay = delay;
}
void Movable::draw(sf::RenderTarget &target, sf::RenderStates states)const //!< Draw function for objects
{

		target.draw(moveSprite);
	
}