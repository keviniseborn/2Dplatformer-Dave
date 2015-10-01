/**
@file Vector2D.cpp
*/

#include "Vector2D.h"
#include <iostream>

Vector2D::Vector2D()  //!< Default consturct, set everything to zero
{
	data[0] = 0;
	data[1] = 0;
}

Vector2D::Vector2D(float allValues) //!< Construtor taking a single value and making all component equal to that value
{
	data[0] = allValues;
	data[1] = allValues;
}


Vector2D::Vector2D(float x, float y) //!< Constructor taking x and y values
{
	data[0] = x;
	data[1] = y;
}


float Vector2D::angle(Vector2D& other) //!< angle between this vector and other
{
	float result;

	result =(data[0]*other.getX()) + (data[1]*other.getY()) /((sqrt(pow(data[0], 2)+pow(data[1], 2)))*(sqrt(pow(other.getX(), 2)+pow(other.getY(), 2))));
	result = cos(result);
	return result;
}


Vector2D Vector2D::getUnitVector() //!< Returns the unit vector of this vector
{
	float unitVector;

	unitVector = (data[0] + data[1])/ (sqrt(pow(data[0], 2) + pow(data[1], 2)));
	return unitVector;
}


float Vector2D::getX() //!< Returns the X component of this vector 
{
	return data[0];
}


float Vector2D::getY() //!< Returns the Y component of this vector
{
	return data[1];
}

void Vector2D::setX(float x)
{
	data[0] = x;
}

void Vector2D::setY(float y)
{
	data[1] = y;
}

float Vector2D::magnitude() //!< Returns the magnitude of this vector
{

	return sqrt(pow(data[0], 2)+pow(data[1], 2));
}

Vector2D Vector2D::operator- (const Vector2D& other) //!< Component wise subtraction
{
	float data2[2];
	data2[0] = data[0]-other.data[0];
	data2[1] = data[1]-other.data[1];
	return Vector2D(data2[0], data2[1]);

}


Vector2D Vector2D::operator+ (const Vector2D& other) //!< Component wise addition
{
	float data2[2];
	data2[0] = data[0]+other.data[0];
	data2[1] = data[1]+other.data[1];
	
	return Vector2D(data2[0], data2[1]);
}


Vector2D Vector2D::operator* (const Vector2D& other) //!< Component wise multiplication
{
	float data2[2];
	data2[0] = data[0]*other.data[0];
	data2[1] = data[1]*other.data[1];

	return Vector2D(data2[0], data2[1]);
}

Vector2D Vector2D::operator* (const float scalar) //!< Component wise scalar multiplication
{
	float data2[2];
	data2[0] = data[0] * scalar;
	data2[1] = data[1] * scalar;
	
	return Vector2D(data2[0], data2[1]);
}

Vector2D Vector2D::operator/ (const float scalar)
{
	return Vector2D(data[0]/scalar,data[1]/scalar);
}

float Vector2D::dotProduct(Vector2D& other) //!< Returns the dot product of this vector with other
{

	return (data[0]*other.getX()) + (data[1]*other.getY());
}
