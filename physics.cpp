#include "physics.h"

/*********************************************************
 * LINEAR INTERPOLATION (mapping version)
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
    // If domain is too small ¡÷ clamp to first mapping
    if (domain <= mapping[0].domain)
        return mapping[0].range;

    // If domain is too large ¡÷ clamp to last mapping
    if (domain >= mapping[numMapping - 1].domain)
        return mapping[numMapping - 1].range;

    // Otherwise find the correct interval
    for (int i = 0; i < numMapping - 1; i++)
    {
        double d0 = mapping[i].domain;
        double d1 = mapping[i + 1].domain;

        if (domain >= d0 && domain <= d1)
        {
            double r0 = mapping[i].range;
            double r1 = mapping[i + 1].range;
            return linearInterpolation(d0, r0, d1, r1, domain);
        }
    }

    // Should never hit here
    return mapping[numMapping - 1].range;
}


/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Uses lookup table with linear interpolation
 *********************************************************/
double gravityFromAltitude(double altitude)
{
    const Mapping table[] =
    {
       {    0.0, 9.807  },
       { 3666.6, 9.795  },
       { 5500.0, 9.7895 },
       {8848.86, 9.77945 },
       {10000.0, 9.776  },
       {43333.3, 9.674  },
       {80000.0, 9.564  }
    };

    return linearInterpolation(table, 7, altitude);
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Uses lookup table with linear interpolation
 *********************************************************/
double densityFromAltitude(double altitude)
{
    const Mapping table[] =
    {
       {     0.0, 1.225      },
       {  3666.6, 0.849372   },
       {  5500.0, 0.69825    },
       { 8848.86, 0.4759719  },
       { 10000.0, 0.4135000  },
       { 43333.3, 0.0030063  },
       { 80000.0, 0.0000185  }
    };

    return linearInterpolation(table, 7, altitude);
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 *********************************************************/
double speedSoundFromAltitude(double altitude)
{
    const Mapping table[] =
    {
       {     0.0, 340.0 },
       {  3666.0, 325.336},
       {  5500.0, 318.0 },
       {  8848.0, 303.76},
       { 10000.0, 299.0 },
       { 43333.0, 328.3329},
       { 80000.0, 269.0 }
    };

    return linearInterpolation(table, 7, altitude);
}

/*********************************************************
 * DRAG FROM MACH
 *********************************************************/
double dragFromMach(double speedMach)
{
    const Mapping table[] =
    {
       { 0.0, 0.0000 },
       { 0.1, 0.0543 },
       { 0.6, 0.1845 },
       { 1.0, 0.4258 },
       { 3.14159, 0.2347 },
       { 5.0, 0.2656 }
    };

    return linearInterpolation(table, 6, speedMach);
}
