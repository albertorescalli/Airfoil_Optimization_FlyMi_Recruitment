#ifndef CONFIG_SETTINGS_H
#define CONFIG_SETTINGS_H

void showConfiguration();       // Function to show current values of simulation parameters
bool modifyConfiguration();     // Function to modify current values of simulation parameters

// Simulation parameters
extern const int panelNodes;            // Number of nodes along the airfoil's surface in xfoil
extern const int iterLimit;             // Maximum number of iterations allowed in xfoil for convergence check (for each alpha)
extern const double alphaStart;         // Starting angle of attack
extern const double alphaEnd;           // Ending angle of attack
extern const double alphaIncrement;     // Increment of alpha at each iteration
extern double reynoldsNumber;           // Reynolds number

// Variables used to calculate Reynolds number. Can be changed by the user during execution
extern double chord;                  // Airfoil chord (trailing edge - leading edge)     [m]
extern double cruiseSpeed;            // Drone cruise speed                               [m/s]
extern double kinematicViscosity;     // Kinematic viscosity of the fluid                 [m^2/s]

#endif // CONFIG_SETTINGS_H