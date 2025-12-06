/**********************************************************************
 * Header File:
 *    SIMULATOR
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once

#include "position.h"
#include "ground.h"
#include "howitzer.h"
#include "uiDraw.h"
#include "uiInteract.h"

class Simulator
{
public:
    Simulator(const Position& posUpperRight) :
        posUpperRight(posUpperRight),
        ground(posUpperRight),
        howitzer()
    {
        // Put howitzer at x = 200m on the ground
        Position start;
        start.setMetersX(200.0);
        start.setMetersY(ground.getElevationMeters(start.getMetersX()));

        howitzer.setPosition(start);
    }

    void callback(const Interface& ui)
    {
        ogstream gout;

        // Draw ground
        ground.draw(gout);

        // Draw howitzer - requires pos, angle, and age
        howitzer.draw(gout);

        // Later we will draw projectile and target (not for Ticket 5)
    }

private:
    Position posUpperRight;
    Ground ground;
    Howitzer howitzer;
};
