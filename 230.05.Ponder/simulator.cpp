/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // for POSITION
#include "acceleration.h"// for ACCELERATION
#include "velocity.h"    // for VELOCITY
#include "angle.h"       // for ANGLE
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <vector>
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
using namespace std;

#define GRAVITY  -1.62

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   // Constructor
   Simulator(const Position & posUpperRight)
      : ground(posUpperRight),
        lander(posUpperRight),
        posUpperRight(posUpperRight)
   {
      // Initialize 50 stars at random positions
      for (int i = 0; i < 50; i++)
      {
         Star star;
         star.reset(posUpperRight.getX(), posUpperRight.getY());
         stars.push_back(star);
      }
   }

   // Display everything on the screen
   void display()
   {
      ogstream gout;

      // Draw the stars (each star twinkles independently)
      for (Star & star : stars)
         star.draw(gout);

      // Draw the ground
      ground.draw(gout);

      // Draw the lander
      lander.draw(thrust, gout);

      // TODO display stats
      // TODO if lander is landed/crashed display approppriate text
   }

   // Handle input and update simulation
   void update(const Interface* pUI)
   {


       if (ground.hitGround(lander.getPosition(), lander.getWidth())) {
           lander.crash();
       }
       else if (ground.onPlatform(lander.getPosition(), lander.getWidth())
           && lander.getSpeed() < lander.getMaxSpeed()) {
           lander.land();
       }
       else {
           thrust.set(pUI);
           lander.coast(lander.input(thrust, GRAVITY), .1);
       }

       if (lander.isDead() || lander.isLanded()) {

           if (pUI->isSpace()) {
               lander.reset(posUpperRight);
           }
       }
   }

   // Members
   Ground ground;
   Lander lander;
   vector<Star> stars;
   Position posUpperRight;
   Thrust thrust;
};

/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // Convert void pointer into a Simulator pointer
   Simulator* pSimulator = (Simulator*)p;

   // Update simulation
   pSimulator->update(pUI);

   // Draw everything
   pSimulator->display();
}

/*********************************
 * Main: Initialize and run the simulator
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the simulator
   Simulator simulator(posUpperRight);

   // Run the simulation
   ui.run(callBack, (void*)&simulator);

   return 0;
}
