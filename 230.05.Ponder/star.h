/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
	void reset(double width, double height) 
	{
		pos.setX(random(0.0, width));
		pos.setY(random(0.0, height));
		phase = random(0, 255); // randomize twinkle phase
	};
	void draw(ogstream gout)
	{
		phase++;
		gout.drawStar(pos);
	};
private:
	Position pos;
	unsigned char phase;
};
