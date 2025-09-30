/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#pragma once

const double PI = 3.141592653589793;

#define TWO_PI 6.28318530718

#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
#include <cmath>     // for floating-point modulus
using namespace std;

class TestAngle;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;






	private:

	
	double normalize(double radians) {
		return fmod(radians, TWO_PI);
	}

	double convertToDegrees(double radians) {
		return radians * (180 / PI);
	}
	
	double convertToDegrees(double degrees) {
		return degrees * (PI / 180);
	}

};


