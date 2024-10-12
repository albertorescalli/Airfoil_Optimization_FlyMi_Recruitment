#ifndef STORE_SIM_RESULTS_H
#define STORE_SIM_RESULTS_H

#include <vector>

// Function to read simulation results from a file, ignoring non-relevant lines
void storeSimulationResults();

extern std::vector<double> alpha;               // Array to store alpha values
extern std::vector<double> cL;                  // Array to store CL values
extern std::vector<double> cD;                  // Array to store CD values
extern std::vector<double> efficiency;          // Array to store CL/CD values

#endif // STORE_SIM_RESULTS_H