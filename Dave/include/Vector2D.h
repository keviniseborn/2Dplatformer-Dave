/**
@file vector2D.h
*/

#ifndef VECTOR2D_H
#define VECTOR2D_H

/*! \class Vector2D
    \a 2D vector
*/

#include <cmath>
#include <cstdlib>

//! \class Vector2D
class Vector2D
{
protected:
	
	float data[2]; //!< Data held by the vector

public:
	Vector2D();  //!< Default constructor, set everything to zero
	Vector2D(float allValues); //!< Construtor taking a single value and making all component equal to that value
	Vector2D(float x, float y); //!< Constructor taking x & y values
	float angle(Vector2D& other); //!< angle between this vector and other
	float dotProduct(Vector2D& other); //!< Returns the dot product of this vector with other
	Vector2D crossProduct(Vector2D& other); //!< Returns the cross product of this vector with other
	Vector2D getUnitVector(); //!< Returns the unit vector of this vector
	float getX(); //!< Returns the X component of this vector 
	float getY(); //!< Returns the Y component of this vector
	void setX(float x); //!< set the x component of the vector
	void setY(float y);//!< set the y component of the vector
	float magnitude(); //!< Returns the magnitude of this vector
	Vector2D operator- (const Vector2D& other); //!< Component wise subtraction
	Vector2D operator+ (const Vector2D& other); //!< Component wise addition
	Vector2D operator* (const Vector2D& other); //!< Component wise multiplication
	Vector2D operator* (const float scalar); //!< Component wise scalar multiplication
	Vector2D operator/ (const float scalar); //!< Component wise scalar division
};

#endif VECTOR2D_H