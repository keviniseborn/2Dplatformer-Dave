/**
@file Collidable.cpp
**/


#include "Collidable.h"

Collidable::Collidable()				//!< default constructor
{
}

void Collidable::setSize(Vector2D &s)	//!< set size of object
{
	size = s;
}

void Collidable::setiMass(float iM)		//!< set inverse mass of object
{
	iMass = iM;

}

void Collidable::setElasticity(float e) //!< set the elasticity of the object
{
	elasticity = e;
}

void Collidable::setNormal(Vector2D &n) //!< set the normal of the object
{
	collidableNormal = n;
}

void Collidable::setDestroyable(bool d) //!< set if the object can be destroyed or not
{
	destroyable = d;
}


Vector2D Collidable::getSize()			//!< getter for Size
{
	return size;
}

float Collidable::getiMass()			//!< getter for inverse mass
{
	return iMass;
}

float Collidable::getElasticity() //!< getter for the elasticity of the object
{
	return elasticity;
}
bool Collidable::getCollides()			//!< getter for if the object collides
{
	return collides;
}
Vector2D Collidable::getNormal()		//!< getter for the normal of the object
{
	return collidableNormal;
}

bool Collidable::getDestroyable()		//!< getter to check if object can be destroyed
{ 
	return destroyable; 
}

bool Collidable::isOnBlock()			//!< getter to check if object is on a block
{
	return onBlock;
}