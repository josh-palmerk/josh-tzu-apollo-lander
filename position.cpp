/***********************************************************************
* Source File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include <cassert>


/************************************************************************
 * UPDATE POSITION
 * Update the current position based on the impulse of velocity
 * taking into account time dilation:
 *
 *   s = s_0 + v t + 1/2 a t^2
 *
 *  x = x + dx t + 1/2 ddx t^2
 *  y = y + dy t + 1/2 ddy t^2
 *************************************************************************/
void Position::add(const Acceleration& a, const Velocity& v, double t)
{
    // kinematic update
    x += v.dx * t + 0.5 * a.ddx * t * t;
    y += v.dy * t + 0.5 * a.ddy * t * t;
}

/******************************************
 * POSITION insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const Position& pt)
{
    out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
    return out;
}

/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, Position& pt)
{
    double xVal;
    double yVal;
    in >> xVal >> yVal;

    pt.setMetersX(xVal);
    pt.setMetersY(yVal);

    return in;
}


Position& Position::operator = (const Position& pt)
{
    if (this != &pt)
    {
        this->x = pt.x;
        this->y = pt.y;
    }
    return *this;
}