/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;


// Constructors
Angle::Angle() : radians(0.0) {}
Angle::Angle(const Angle& rhs) : radians(normalize(rhs.radians)) {}
Angle::Angle(double degrees) : radians(normalize(convertToRadians(degrees))) {}

// Getters
double Angle::getDegrees() const
{
	return convertToDegrees(radians);
}

double Angle::getRadians() const
{
	return radians;
}

// Setters
void Angle::setDegrees(double degrees)
{
	radians = normalize(convertToRadians(degrees));
}

void Angle::setRadians(double radiansIn)
{
	radians = normalize(radiansIn);
}

void Angle::reverse()
{
	radians = normalize(radians + M_PI);
}

Angle& Angle::add(double delta)
{
	radians = normalize(radians + delta);
	return *this;
}

void Angle::setUp()
{
	radians = 0.0;
}

void Angle::setDown()
{
	radians = M_PI;
}

void Angle::setRight()
{
	radians = M_PI / 2.0;
}

void Angle::setLeft()
{
	radians = 3.0 * M_PI / 2.0;
}

bool Angle::isUp() const
{
	return cos(radians) > 0.0;
}

bool Angle::isDown() const
{
	return cos(radians) < 0.0;
}

bool Angle::isRight() const
{
	return sin(radians) > 0.0;
}

bool Angle::isLeft() const
{
	return sin(radians) < 0.0;
}



void Angle::setDxDy(double dx, double dy)
{
	radians = normalize(atan2(dx, dy));
}

// Private helpers
double Angle::normalize(double radiansIn) const
{
	// handle negative values
	while (radiansIn < 0.0)
		radiansIn += 2.0 * M_PI;

	// handle values >= 2π
	while (radiansIn >= 2.0 * M_PI)
		radiansIn -= 2.0 * M_PI;

	return radiansIn;
}

double Angle::convertToDegrees(double radians) const
{
	return radians * 360.0 / (2.0 * M_PI);
}

double Angle::convertToRadians(double degrees) const
{
	return degrees * (2.0 * M_PI) / 360.0;
}
