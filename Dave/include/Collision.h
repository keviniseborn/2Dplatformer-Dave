/**
@file Collision.h
*/

#ifndef COLLISION_H
#define COLLISION_H
#include "Collidable.h"
#include <Math.h>
#include <algorithm>

/*! \class Collision
	\Handles the collision events in the game
*/

class Collision
{

public:

	Collision(); //!< default constructor
	void resolve(Collidable &p, Collidable &b); //!< resolve collision function
	bool AABBvsAABB(Collidable &p, Collidable &b); //!< AABB vs AABB collision detection function
	void collisionNormal(Collidable &p, Collidable &b); //!< calculate collision normal function
};

#endif