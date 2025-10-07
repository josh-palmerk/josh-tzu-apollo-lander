/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

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
   Angle()                 : radians(0)  {}
   Angle(const Angle& rhs) : radians(rhs.radians)  {}
   Angle(double degrees)   : radians(normalize(degrees * (M_PI / 180)))  {}

   // Getters
   double getDegrees() const { return radians * (180 / M_PI); }
   double getRadians() const { return radians; }

   // Setters
   void setDegrees(double degrees) { this->radians = normalize(degrees * (M_PI / 180)); }
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp() { this->radians = 0;  }
   void setDown() { this->radians = M_PI; }
   void setRight() { this->radians = M_PI / 2; }
   void setLeft() { this->radians = 1.5 * M_PI; }
   void reverse() { this->radians += M_PI; }
   Angle& add(double delta) { radians = normalize(radians + delta); return *this; }

private:
   double normalize(double radians) const;
   double convertToDegrees(double radians) const;
   double convertToRadians(double radians) const;
    
   double radians;   // 360 degrees equals 2 PI radians
};

