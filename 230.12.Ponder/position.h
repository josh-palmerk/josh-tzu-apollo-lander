/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once

#include <iostream>
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestGround;
class TestHowitzer;
class TestProjectile;

/*********************************************
 * Position
 * A single position on the field in Meters
 *********************************************/
class Position
{
public:
   friend ::TestPosition;
   friend ::TestGround;
   friend ::TestHowitzer;
   friend ::TestProjectile;

   // constructors
   Position()                     : x(0.0), y(0.0) {}
   Position(double xMeters, double yMeters) : x(xMeters), y(yMeters) {}
   Position(const Position & pt)  : x(pt.x), y(pt.y) {}
   Position& operator = (const Position& pt);

   // getters (meters)
   double getMetersX()       const { return x; }
   double getMetersY()       const { return y; }

   // getters (pixels)
   double getPixelsX()       const { return x / metersFromPixels; }
   double getPixelsY()       const { return y / metersFromPixels; }

   // setters
   void setZoom(double z) { metersFromPixels = z; }         // static: affects all Position instances
   static double getZoom() { return metersFromPixels; }

   void setMeters(double xMeters, double yMeters) { x = xMeters; y = yMeters; }
   void setMetersX(double xMeters)       { x = xMeters; }
   void setMetersY(double yMeters)       { y = yMeters; }

   void setPixelsX(double xPixels)       { x = xPixels * metersFromPixels; }
   void setPixelsY(double yPixels)       { y = yPixels * metersFromPixels; }

   double addMetersX(double dxMeters) { x += dxMeters; return x; }
   double addMetersY(double dyMeters) { y += dyMeters; return y; }
   double addPixelsX(double dxPixels) { x += dxPixels * metersFromPixels; return x; }
   double addPixelsY(double dyPixels) { y += dyPixels * metersFromPixels; return y; }

   void add(const Acceleration& a, const Velocity& v, double t);

   void reverse() { x = -x; y = -y; }

   // static zoom (meters-per-pixel)
   static double metersFromPixels;

private:
   double x;                 // horizontal position (meters)
   double y;                 // vertical position (meters)
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position& pt);
std::istream & operator >> (std::istream & in,        Position& pt);

/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};
