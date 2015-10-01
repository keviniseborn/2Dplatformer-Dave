/**
@file Blocks.cpp
*/

#include "Collision.h"
#include <iostream>




Collision::Collision()
{

}


bool Collision::AABBvsAABB(Collidable& p, Collidable& b)//!< Checking for AABB collision
{
	//! checks if an object hasn't collided, returns true if all checks fail
	if(p.getPos().getX() > b.getPos().getX() + b.getSize().getX()) return false;
	if(p.getPos().getX() + p.getSize().getX() < b.getPos().getX()) return false; 
	if(p.getPos().getY() > b.getPos().getY()+ b.getSize().getY()) return false;
	if(p.getPos().getY() + p.getSize().getY() < b.getPos().getY())return false;

	return true;
	
} 

void Collision::collisionNormal(Collidable &p, Collidable &b)//!< Calculating AABB collision normal
{
	//! Calculate the collision normal from the manifold of 2 objects intersecting
	Vector2D manifold;

	if(p.getPos().getX() < b.getPos().getX())
	{
		manifold.setX((p.getPos().getX() + p.getSize().getX()) - b.getPos().getX());
	}
	if(p.getPos().getY() < b.getPos().getY())
	{
		manifold.setY((p.getPos().getY() + p.getSize().getY()) - b.getPos().getY());
	}


	if(p.getPos().getX() > b.getPos().getX())
	{
		manifold.setX((b.getPos().getX() + b.getSize().getX()) - p.getPos().getX());
	}
	if(p.getPos().getY() > b.getPos().getY())
	{
		manifold.setY((b.getPos().getY() + b.getSize().getY()) - p.getPos().getY());
	}
	
	if(manifold.getX() > manifold.getY() && p.getPos().getY() > b.getPos().getY()){ p.setNormal(Vector2D(0,1)); p.onBlock =false; b.setNormal(Vector2D(0,-1));}
	if(manifold.getX() > manifold.getY() && p.getPos().getY() < b.getPos().getY()){ p.setNormal(Vector2D(0,-1)); p.onBlock =true; p.setAcc(Vector2D(0.f, 0.f)); b.setNormal(Vector2D(0,1)); b.setAcc(Vector2D(0.f, 0.f));}

	if(manifold.getY() > manifold.getX() && p.getPos().getX() < b.getPos().getX()){ p.setNormal(Vector2D(-1,0)); p.onBlock =false; b.setNormal(Vector2D(1,0));}
	if(manifold.getY() > manifold.getX() && p.getPos().getX() > b.getPos().getX()){ p.setNormal(Vector2D(1,0)); p.onBlock =false; b.setNormal(Vector2D(-1,0));}
	
}

void Collision::resolve(Collidable& p, Collidable&b)
{
	//!normal calculations for position correction
	Vector2D collisionNormal;
	float magnitude;
	
	collisionNormal.setX(b.getPos().getX() - p.getPos().getX());
	collisionNormal.setY(b.getPos().getY() - p.getPos().getY());
	magnitude = collisionNormal.magnitude();
	
	//!position correction
	float pDepth;
	float cScalar;
	Vector2D c;
	Vector2D c1;
	Vector2D c2;
	float slop = 0.2f;
	float percent = 0.3f;
	
	//!penetration depth calculations
	pDepth = sqrt((p.getSize().getY() * p.getSize().getY()) + (p.getSize().getX() * p.getSize().getX()) + (b.getSize().getY() * b.getSize().getY()) + (b.getSize().getX() * b.getSize().getX())) - magnitude;
	pDepth = b.getPos().getY() - (p.getPos().getY()+(p.getSize().getY()));
	//scalar calculation for both objects 
	cScalar = ((pDepth-slop)/(p.iMass+b.iMass))*percent;


	c1.setX(cScalar*p.getNormal().getX());
	c1.setY(cScalar*p.getNormal().getY());

	c2.setX(cScalar*b.getNormal().getX());
	c2.setY(cScalar*b.getNormal().getY());

	p.setPos(Vector2D((p.getPos().getX() - c1.getX() * p.iMass),(p.getPos().getY() - c1.getY() * p.iMass)));
	b.setPos(Vector2D((b.getPos().getX() - c2.getX() * b.iMass),(b.getPos().getY() - c2.getY() * b.iMass)));
	

	
	//!Impulse resolution
	Vector2D relativeV; //!< relative velocity
	float relativeVnormalp;
	float relativeVnormalb;
	float j;	
	float newVelX; //!< new velocity in Y
	float newVelY; //!< new velocity in Y
	float e; //!<elasticity
	
	//!scalar calculations for new velcotities
	relativeV.setX(p.getVel().getX() - b.getVel().getX());
	relativeV.setY(p.getVel().getY() - b.getVel().getY());

	relativeVnormalp = relativeV.getX() * p.getNormal().getX() + relativeV.getY() * p.getNormal().getY();
	relativeVnormalb = relativeV.getX() * b.getNormal().getX() + relativeV.getY() * b.getNormal().getY();
	e = std::min(p.elasticity, b.elasticity);

	//!Velocity for Movable p
	j = (-(1+e)*relativeVnormalp)  / (p.iMass + b.iMass);
	newVelX = p.getVel().getX() + ((j * p.getNormal().getX()) * (p.iMass));
	newVelY = p.getVel().getY() + ((j * p.getNormal().getY()) * (p.iMass));
	p.setVel(Vector2D(newVelX, newVelY));

	//!Velocity for Movable b
	j = (-(1+e)*relativeVnormalb)  / (p.iMass + b.iMass);
	newVelX = b.getVel().getX() - ((j * b.getNormal().getX()) * (b.iMass));
	newVelY = b.getVel().getY() - ((j * b.getNormal().getY()) * (b.iMass));
	b.setVel(Vector2D(newVelX, newVelY));
	
	if(p.getPlayable() == true)
	{
		p.setNormal(Vector2D(0.f,0.f));
	}
}