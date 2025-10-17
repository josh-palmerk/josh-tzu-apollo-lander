/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
	this->angle.setUp();
	status = PLAYING;
	fuel = 5000.0;
	velocity.setDX(random(-10.0, -4.0));
	velocity.setDY(random(-2.0, 2.0));
	pos = Position(posUpperRight.getX() - 1, random(posUpperRight.getY() * .75, posUpperRight.getY() * .95));


}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
	gout.drawLander(pos, angle.getRadians());
	gout.drawLanderFlames(pos, angle.getRadians(), thrust.isMain(), thrust.isClock(), thrust.isCounter());
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   Acceleration a;

   a.setDDY(gravity);

   angle.add(thrust.rotation());
   if (thrust.isClock() || thrust.isCounter()) fuel -= 1.0;
   if (fuel <= 0.0) fuel = 0.0;

   if (fuel > 0.0 && thrust.isMain())
   {
	   fuel -= 10.0;
	   if (fuel <= 0.0) fuel = 0.0;
	   //edit fuel amount here?
	   Acceleration thrustAcc;
	   thrustAcc.set(angle, thrust.mainEngineThrust());
	   thrustAcc.setDDX(-thrustAcc.getDDX());
	   a.add(thrustAcc);

   }

   return a;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   // update position, then increase velocity for next tick
   pos.add(acceleration, velocity, time);
   velocity.add(acceleration, time);
}
