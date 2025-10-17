/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

using namespace std;
#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159
#include <iomanip>

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestLander;
   
   // Constructors
   Angle();
   Angle(const Angle& rhs);
   Angle(double degrees);

   // Getters
   double getDegrees() const;
   double getRadians() const;

   // Setters
   void setDegrees(double degrees);
   void setRadians(double radians);
   void setUp();
   void setDown();
   void setRight();
   void setLeft();
   void reverse();
   Angle& add(double delta);

private:
	double normalize(double radians) const;
	double convertToDegrees(double radians) const;
	double convertToRadians(double degrees) const;

	double radians;
};

