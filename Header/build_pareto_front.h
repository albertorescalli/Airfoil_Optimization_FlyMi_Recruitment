#ifndef BUILD_PARETO_FRONT_H
#define BUILD_PARETO_FRONT_H

#include <vector>

// Function to build the Pareto front from the given data
void buildParetoFront(const std::vector<double>& alpha, const std::vector<double>& cL, const std::vector<double>& cD);

// Global vector that stores the Pareto front
extern std::vector<std::pair<double, double>> paretoFront;

#endif // BUILD_PARETO_FRONT_H