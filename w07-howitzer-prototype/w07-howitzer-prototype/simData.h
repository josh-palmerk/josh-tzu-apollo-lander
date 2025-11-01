#pragma once
#ifndef SIMDATA_H
#define SIMDATA_H

#include <vector>

class SimData {
public:
    // --- Drag Coefficient vs Mach ---
    const std::vector<double> machTable = {
        0.000, 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980,
        1.000, 1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000
    };

    const std::vector<double> dragCoeffTable = {
        0.0000, 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002,
        0.4258, 0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656
    };

    // --- Air Density vs Altitude (kg/m³) ---
    const std::vector<double> altitudeDensityTable = {
        0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
        10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000,
        70000, 80000
    };

    const std::vector<double> densityTable = {
        1.2250000, 1.1120000, 1.0070000, 0.9093000, 0.8194000,
        0.7364000, 0.6601000, 0.5900000, 0.5258000, 0.4671000,
        0.4135000, 0.1948000, 0.0889100, 0.0400800, 0.0184100,
        0.0039960, 0.0010270, 0.0003097, 0.0000828, 0.0000185
    };

    // --- Speed of Sound vs Altitude (m/s) ---
    const std::vector<double> altitudeSpeedSoundTable = {
        0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
        10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000,
        70000, 80000
    };

    const std::vector<double> speedOfSoundTable = {
        340, 336, 332, 328, 324, 320, 316, 312, 308, 303,
        299, 295, 295, 295, 305, 324, 337, 319, 289, 269
    };

    // --- Gravity vs Altitude (m/s²) ---
    const std::vector<double> altitudeGravityTable = {
        0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
        10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000,
        70000, 80000
    };

    const std::vector<double> gravityTable = {
        9.807, 9.804, 9.801, 9.797, 9.794, 9.791, 9.788, 9.785, 9.782,
        9.779, 9.776, 9.761, 9.745, 9.730, 9.715, 9.684, 9.654, 9.624,
        9.594, 9.564
    };
};

#endif // SIMDATA_H
