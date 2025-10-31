#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "SimData.h"
//#include "HowitzerSim.h"

SimData data;
//HowitzerSim sim(...);

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
    const SimData& data;  // reference to lookup tables


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
    HowitzerSim(const SimData& simData, double m_kg, double caliber_m, double muzzleVel_mps, double angleDeg_fromVertical)
        : data(simData),
        mass(m_kg), caliber(caliber_m), posX(0.0), posY(0.0),
        velX(0.0), velY(0.0), accelX(0.0), accelY(0.0),
        hangTime(0.0), maxAltitude(0.0), distance(0.0)
    {
        double angleRad = angleDeg_fromVertical * M_PI / 180.0;
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
    

    void step() {
        // --- 1. Interpolate gravity based on current altitude ---
        double localGravity = linearInterpolate(
            posY,
            data.altitudeGravityTable,
            data.gravityTable
        );

        // --- 2. Interpolate air density based on current altitude ---
        double localDensity = linearInterpolate(
            posY,
            data.altitudeDensityTable,
            data.densityTable
        );

        // --- 3. Compute drag force ---
        const double Cd = 0.3;              // drag coefficient (constant)
        const double diameter = 0.15489;    // m (projectile diameter)
        const double area = M_PI * std::pow(diameter / 2.0, 2); // m² (cross-sectional area)

        // Total velocity magnitude
        double vMag = std::sqrt(velX * velX + velY * velY);

        // Drag force magnitude (N)
        double Fd = 0.5 * localDensity * Cd * area * vMag * vMag;

        // Convert to acceleration magnitude (m/s²)
        double dragAccelMag = Fd / mass;

        // Angle of motion (radians)
        double theta = std::atan2(velY, velX);

        // Components of drag acceleration (opposite direction of velocity)
        double dragAccelX = -dragAccelMag * std::cos(theta);
        double dragAccelY = -dragAccelMag * std::sin(theta);

        // --- 4. Combine accelerations ---
        accelX = dragAccelX;
        accelY = -localGravity + dragAccelY;

        // --- 5. Update position using s = s0 + v*t + ½*a*t² ---
        double newPosX = calcDisplacement(posX, velX, accelX, TIMESTEP);
        double newPosY = calcDisplacement(posY, velY, accelY, TIMESTEP);

        // --- 6. Update velocity using v = v0 + a*t ---
        double newVelX = calcVelocity(velX, accelX, TIMESTEP);
        double newVelY = calcVelocity(velY, accelY, TIMESTEP);

        // --- 7. Commit updates ---
        posX = newPosX;
        posY = newPosY;
        velX = newVelX;
        velY = newVelY;

        hangTime += TIMESTEP;
        if (posY > maxAltitude) maxAltitude = posY;
        distance = posX;

        // --- 8. Clamp to ground ---
        if (posY <= 0.0 && hangTime > 0.0) {
            posY = 0.0;
            velY = 0.0;
            accelY = 0.0;
        }
    }


    // --- Linear interpolation using full table ---
    // Returns y corresponding to given x based on provided tableX/tableY.
    double linearInterpolate(double x,
        const std::vector<double>& tableX,
        const std::vector<double>& tableY) const
    {
        if (tableX.size() != tableY.size() || tableX.empty())
            throw std::invalid_argument("Invalid interpolation table: mismatched sizes or empty.");

        // If x is outside range, clamp to endpoints
        if (x <= tableX.front()) return tableY.front();
        if (x >= tableX.back())  return tableY.back();

        // Find bounding indices
        for (size_t i = 0; i < tableX.size() - 1; ++i) {
            if (x >= tableX[i] && x <= tableX[i + 1]) {
                double x1 = tableX[i];
                double x2 = tableX[i + 1];
                double y1 = tableY[i];
                double y2 = tableY[i + 1];
                double t = (x - x1) / (x2 - x1);
                return y1 + t * (y2 - y1);
            }
        }

        // Should never reach here if table is sorted
        return tableY.back();
    }

    // --- Simple 2-point linear interpolation (useful for ground impact) ---
    // Interpolates Y for a given X, given two points (x1,y1) and (x2,y2)
    double linearInterpolate(double x, double x1, double y1, double x2, double y2) const {
        if (x2 == x1) return y1; // avoid divide-by-zero
        double t = (x - x1) / (x2 - x1);
        return y1 + t * (y2 - y1);
    }

    // --- Find impact location between timesteps ---
    // Given previous (x1, y1) and current (x2, y2) positions, find x where y = 0
    double interpolateGroundImpact(double x1, double y1, double x2, double y2) const {
        if ((y1 > 0 && y2 > 0) || (y1 < 0 && y2 < 0)) {
            // No ground crossing
            return std::nan("");
        }
        // Linear interpolation to find x at which y = 0
        return linearInterpolate(0.0, y1, x1, y2, x2);
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
    SimData data;

    // Launch angle: 75 degrees from vertical (user said 0 degrees is straight up)
    const double launchAngleFromVertical = 75.0;  // deg

    HowitzerSim sim(data, projMass, projDiam_m, muzzleVel, launchAngleFromVertical);

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
