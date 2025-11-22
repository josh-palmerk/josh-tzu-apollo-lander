/***********************************************************************
 * Source File:
 *    ACCELERATION 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <iostream>
#include <cmath>
#include <numbers>

/*********************************************
 * ACCELERATION : ADD
 *  a += a
 *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
     ddx = acceleration.getDDX() + ddx;
     ddy = acceleration.getDDY() + ddy;
}

/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & angle, double magnitude)
{
    double a = angle.getRadians();
    ddx = magnitude * std::sin(a);
    ddy = magnitude * std::cos(a);
}
