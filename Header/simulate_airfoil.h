#ifndef SIMULATE_AIRFOIL_H
#define SIMULATE_AIRFOIL_H
#include <string>

// Function to run airfoil simulation in xfoil
void runSimulation();

// Variable to store the name of the file where simulation results will be saved
extern std::string simDataFile;

#endif // SIMULATE_AIRFOIL_H