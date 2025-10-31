#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//#define GRAVITY = 9.81;
//#define TIMESTEP = 0.01;

// Simple physics sim for an M795 shell fired from an M777 (starter version).
// - Angle convention: 0 degrees = straight up. Angle increases toward the forward (horizontal) direction.
// - Timesteps are fixed at 0.01 s.
// - No drag, no wind, no rotation yet — just gravity and kinematics.

class HowitzerSim {
private:
    // --- Constants ---
    static constexpr double GRAVITY = 9.8;   // m/s^2 downward
    static constexpr double TIMESTEP = 0.01;  // s

    // --- Projectile properties ---
    double mass;      // kg
    double caliber;   // m (diameter)
    double inertia;   // kg*m^2 (rotational inertia stub)

    // --- State ---
    double posX;      // m, horizontal distance
    double posY;      // m, altitude
    double velX;      // m/s, horizontal velocity (positive forward)
    double velY;      // m/s, vertical velocity (positive upward)
    double accelX;    // m/s^2, horizontal accel
    double accelY;    // m/s^2, vertical accel

    // --- Tracking ---
    double hangTime;    // s, time since launch
    double maxAltitude; // m
    double distance;    // m (horizontal)

public:
    // Constructor
    // angleDeg_fromVertical: 0 = straight up, 90 = horizontal
    HowitzerSim(double m_kg, double caliber_m, double muzzleVel_mps, double angleDeg_fromVertical)
        : mass(m_kg), caliber(caliber_m), posX(0.0), posY(0.0),
        velX(0.0), velY(0.0), accelX(0.0), accelY(0.0),
        hangTime(0.0), maxAltitude(0.0), distance(0.0)
    {
        // Convert angle: user supplies degrees from vertical
        double angleRad = angleDeg_fromVertical * M_PI / 180.0;

        // Since 0° is straight up, vertical component = v * cos(theta)
        // horizontal component = v * sin(theta)
        velY = muzzleVel_mps * std::cos(angleRad);
        velX = muzzleVel_mps * std::sin(angleRad);

        inertia = calculateInertia();
    }

    // Approximate inertia for a solid cylinder (stub)
    double calculateInertia() const {
        double radius = caliber / 2.0;
        return 0.5 * mass * radius * radius;
    }

    // --- Kinematics helpers ---
    double calcDisplacement(double s0, double v, double a, double t) const {
        return s0 + v * t + 0.5 * a * t * t;
    }

    double calcVelocity(double v0, double a, double t) const {
        return v0 + a * t;
    }

    // Perform one explicit Euler update of position & velocity
    void step() {
        // Gravity only, for now
        accelX = 0.0;
        accelY = -GRAVITY;

        // Update position using s = s0 + v*t + ½*a*t²
        double newPosX = calcDisplacement(posX, velX, accelX, TIMESTEP);
        double newPosY = calcDisplacement(posY, velY, accelY, TIMESTEP);

        // Update velocity using v = v0 + a*t
        double newVelX = calcVelocity(velX, accelX, TIMESTEP);
        double newVelY = calcVelocity(velY, accelY, TIMESTEP);

        // Commit updates
        posX = newPosX;
        posY = newPosY;
        velX = newVelX;
        velY = newVelY;

        hangTime += TIMESTEP;
        if (posY > maxAltitude) maxAltitude = posY;
        distance = posX;

        

    }

    // Accessors
    double getHangTime()   const { return hangTime; }
    double getAltitude()   const { return posY; }
    double getMaxAltitude()const { return maxAltitude; }
    double getDistance()   const { return distance; }



    bool hasHitGround() const {
        // hit ground if posY == 0 and we have advanced at least one timestep
        return (posY <= 0.0) && (hangTime > 0.0);
    }

    // Debug print (formatted)
    void printState() const {
        std::cout << std::fixed << std::setprecision(4)
            << "t=" << hangTime << " s | x=" << posX << " m | y=" << posY << " m"
            << " | vx=" << velX << " m/s | vy=" << velY << " m/s\n";
    }
};


int main() {
    // M777/M795 specifics provided:
    // Muzzle velocity: 827.0 m/s
    // Projectile: M795 155 mm, mass 46.7 kg, diameter 154.89 mm
    const double muzzleVel = 827.0;               // m/s
    const double projMass = 46.7;               // kg
    const double projDiam_m = 154.89 / 1000.0;    // mm -> m

    // Launch angle: 75 degrees from vertical (user said 0 degrees is straight up)
    const double launchAngleFromVertical = 75.0;  // deg

    HowitzerSim sim(projMass, projDiam_m, muzzleVel, launchAngleFromVertical);

    std::cout << "Simulating 20 timesteps (" << 20 << " * 0.01 s) for M777 -> M795\n";
    std::cout << "(Angle convention: 0° = straight up; here angle = "
        << launchAngleFromVertical << "° from vertical)\n\n";

    // Run exactly 20 timesteps and print state each step
     int steps = 0;
    //for (int i = 0; i < steps; ++i) {
    //    sim.step();
    //    sim.printState();
    //}

     while (sim.getAltitude() > 0 || steps == 0) {
         sim.step();
         sim.printState();
         steps++;
     }


    std::cout << "\nSummary after " << steps << " steps:\n"
        << "Hang time (s): " << sim.getHangTime() << "\n"
        << "Altitude (m): " << sim.getAltitude() << "\n"
        << "Max altitude (m): " << sim.getMaxAltitude() << "\n"
        << "Distance (m): " << sim.getDistance() << "\n";

    return 0;
}
