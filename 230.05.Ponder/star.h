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
		pos = Position(random(0.0, width), random(0.0, height));
	};
	void draw(ogstream gout)
	{
		phase++;
	};
private:
	Position pos;
	unsigned char phase;
};
