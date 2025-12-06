/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 04: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/


#define TWO_PI 6.28318530718

#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

class TestAngle;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;

public:
   // Default constructor
   Angle()                   { }
   Angle(const Angle & rhs)  { }
   Angle(double degrees)     { }

   // Getters
   double getDegrees() const { return -1.0; }
   double getRadians() const { return -1.0; }

   // Setters
   void setDegrees(double degrees) { }
   void setRadians(double radians) { }

   // Display
   void display(ostream & out) const { }


   /**************** OPERATORS *******************************/

   //assignment operator - josh

   Angle operator=(const Angle& rhs) { 
	   radians = rhs.radians;
	   return *this; 
   }
   Angle operator=(double radians) { 
	   setRadians(radians); 
	   return *this; 
   }


   //negative - josh
   Angle operator-() const {
	   Angle negAngle;
	   negAngle.radians = normalize(-radians);
	   return negAngle;
   }



   //equals/not equals - josh
   Angle operator==(const Angle& rhs) const {
	   return radians == rhs.radians;
   }
   Angle operator!=(const Angle& rhs) const {
	   return radians != rhs.radians;
   }



   // insert - tzu

   //extract - tzu

   // increment/decrement - tzu


private:
   // Convert functions
   double convertToDegrees(double radians) const { return -1.0; }
   double convertToRadians(double degrees) const { return -1.0; }

   // Normalize
   double normalize(double radians) const { return  -1.0; }

   double radians;
};
