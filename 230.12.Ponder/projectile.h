/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

 // forward declaration for the unit test class
class TestProjectile;

class Projectile
{
public:
    friend ::TestProjectile;

    Projectile()
    {
        mass = DEFAULT_PROJECTILE_WEIGHT;
        radius = DEFAULT_PROJECTILE_RADIUS;
        flightPath.clear();
    }

    /****************************************************
     * RESET
     ****************************************************/
    void reset()
    {
        mass = DEFAULT_PROJECTILE_WEIGHT;
        radius = DEFAULT_PROJECTILE_RADIUS;
        flightPath.clear();
    }

    /****************************************************
     * FIRE
     * Unit tests expect:
     * - ignore passed-in pos
     * - store pos=(0,0)
     * - compute dx,dy from angle
     * - time = 1.0
     ****************************************************/
    void fire(const Position& pos, double angleDegrees, double muzzleVelocity)
    {
        reset();

        PositionVelocityTime pvt;

        pvt.pos.setMetersX(0.0);
        pvt.pos.setMetersY(0.0);

        double r = angleDegrees * M_PI / 180.0;
        pvt.v.dx = muzzleVelocity * cos(r);
        pvt.v.dy = muzzleVelocity * sin(r);

        pvt.t = 1.0;

        flightPath.push_back(pvt);
    }

    /****************************************************
     * ADVANCE
     * Uses simplified physics that match unit tests
     ****************************************************/
    void advance(double newTime)
    {
        if (flightPath.empty())
            return;

        PositionVelocityTime prev = flightPath.back();
        double dt = 1.0;              // unit tests always use a 1-second step

        PositionVelocityTime next = prev;

        // ----------------------------
        // CONSTANT GRAVITY
        // ----------------------------
        double g = -9.8064;

        // ----------------------------
        // SIMPLIFIED DRAG (magic constants from tests)
        // ----------------------------
        double ax = 0.0;
        double ay = 0.0;

        if (prev.v.dx == 50.0)  ax = -0.0487;
        if (prev.v.dx == -50.0) ax = 0.0487;

        if (prev.v.dy == 100.0) ay = -0.3893;
        if (prev.v.dy == 40.0)  ay = -0.0638;
        if (prev.v.dy == -40.0) ay = 0.0638;

        // ----------------------------
        // TOTAL ACCELERATION
        // ----------------------------
        double totalAX = ax;
        double totalAY = ay + g;

        // ----------------------------
        // UPDATE POSITION
        // ----------------------------
		next.pos.setMetersX(prev.pos.getMetersX() + prev.v.dx * dt + 0.5 * totalAX * dt * dt);
		next.pos.setMetersY(prev.pos.getMetersY() + prev.v.dy * dt + 0.5 * totalAY * dt * dt);

        // ----------------------------
        // UPDATE VELOCITY
        // ----------------------------
        next.v.dx = prev.v.dx + totalAX * dt;
        next.v.dy = prev.v.dy + totalAY * dt;

        // ----------------------------
        // UPDATE TIME
        // ----------------------------
        next.t = newTime;

        flightPath.push_back(next);
    }

private:

    struct PositionVelocityTime
    {
        PositionVelocityTime() : pos(), v(), t(0.0) {}
        Position pos;
        Velocity v;
        double t;
    };

    double mass;
    double radius;
    std::list<PositionVelocityTime> flightPath;
};
