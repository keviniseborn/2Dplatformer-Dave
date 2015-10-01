/**
@file Collidable.h
*/

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Movable.h"

/*! \class Collidable
	\Class for all the collidable objects in the game
	\Contains all the necessary information for collisions
*/

class Collidable: public Movable
{
	
	friend class Collision; //!< friend class with collision class

protected:
	

	Vector2D size;					//!< Vector2D of size
	Vector2D collidableNormal;		//!< Vector2D of the normal after colliding
	float iMass;					//!< inverse mass of object
	bool collides;					//!< if object collides
	float elasticity;				//!< elasticity of an object
	bool destroyable;				//!< if object is destroyable or not
	bool onBlock;					//!< if the object is ontop of a block

public:
	Collidable();					//!< default constructor

	void setSize(Vector2D &s);		//!< set size of object
	void setiMass(float iM);		//!< set inverse mass of object
	void setElasticity(float e);	//!< set elasticity of object
	void setNormal(Vector2D &n);	//!< set the normal of the object
	void setDestroyable(bool d);	//!< change if the object can be destroyed or not

	Vector2D getSize();				//!< getter for Size
	float getiMass();				//!< getter for inverse mass
	float getElasticity();			//!< getter for inverse mass
	bool getCollides();				//!< getter for if the object collides
	Vector2D getNormal();			//!< getter for the object collision normal
	bool getDestroyable();			//!< getter to check if object can be destroyed
	bool isOnBlock();				//!< getter to check if object is on block

};
#endif