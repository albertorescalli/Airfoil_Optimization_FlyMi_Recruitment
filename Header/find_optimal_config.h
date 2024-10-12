#ifndef FIND_OPTIMAL_CONFIG_H
#define FIND_OPTIMAL_CONFIG_H

// Global variables used to store optimal configuration values
extern double alphaOptimal;
extern double cLOptimal;
extern double cDOptimal;
extern double efficiencyOptimal;

// Function to find optimal configuration within the Pareto front
void findOptimalConfig();

#endif // FIND_OPTIMAL_CONFIG_H