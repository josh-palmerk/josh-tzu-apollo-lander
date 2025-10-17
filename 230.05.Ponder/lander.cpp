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
   //pos.setX(-99.9);
   return Acceleration();
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   pos.addX(acceleration.getDDX() * time);
   pos.addY(acceleration.getDDY() * time);
   
}
