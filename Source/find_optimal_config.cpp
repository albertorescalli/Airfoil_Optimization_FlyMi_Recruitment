/*
    This program is responsible for identifying the optimal configuration for an airfoil based on
    the Pareto front calculated from simulation results. The optimal configuration is determined by finding
    the angle of attack (alpha) and associated values for lift (cL), drag (cD), and efficiency (cL/cD) that 
    maximize the trade-off between these parameters.

    The function `findOptimalConfig` takes the first point from the Pareto front as the optimal solution (as it is 
    the first dominant value of the Pareto front, and none of the following ones can have higher values of both cL 
    and efficieny) and retrieves the corresponding angle of attack (alpha) along with its lift, drag, and efficiency values.
    The results are displayed to the user.

    If no points are found in the Pareto front or if the matching values cannot be located in the simulation data,
    an error message is printed, and the program exits.
*/

#include "../Header/find_optimal_config.h"
#include "../Header/build_pareto_front.h"
#include "../Header/store_sim_results.h"

#include <iostream>
#include <vector>
#include <utility>

// Global variables to store the optimal configuration values
double alphaOptimal;
double cLOptimal;
double cDOptimal;
double efficiencyOptimal;

// Function to find the optimal configuration from the Pareto front
void findOptimalConfig() {
    // Reset optimal values before each new simulation
    alphaOptimal = 0.0;
    cLOptimal = 0.0;
    cDOptimal = 0.0;
    efficiencyOptimal = 0.0;

    // If the Pareto front is empty, display an error and exit
    if (paretoFront.empty()) {
        std::cerr << "\nERROR: Could not run optimization process." << std::endl;
        exit(1);
    }
    /*
        The first point in the Pareto front is considered the optimal point
        This is because it represents the first non-dominated solution in the Pareto front.
        A point is considered non-dominated if there is no other point in the set that has both
        a higher lift coefficient (cL) and a higher efficiency (cL/cD). In a Pareto optimization context, 
        the goal is to maximize both objectives (lift and efficiency), but improving one often comes at
        the cost of the other. As we move along the Pareto front, each subsequent point represents a trade-off
        where an improvement in one objective would lead to a reduction in the other. 
        By selecting the first point, we prioritize a solution that provides the highest lift and efficiency
        without any superior trade-off among subsequent points in the front.
    */
    std::pair<double, double> optimalPoint = paretoFront.front();

    std::cout << "\nOptimal values:" << std::endl;

    // Find the corresponding alpha index for the optimal point
    for (size_t i = 0; i < alpha.size(); ++i) {
        if (cL[i] == optimalPoint.first && efficiency[i] == optimalPoint.second) {
            alphaOptimal = alpha[i];                    // Store the optimal alpha value
            cDOptimal = cD[i];                          // Store the optimal cD value
            cLOptimal = optimalPoint.first;             // Store the optimal cL value
            efficiencyOptimal = optimalPoint.second;    // Store the optimal efficiency value
            printf("  Alpha: %.5f\n  CL: %.5f\n  CD: %.5f\n  L/D: %.5f\n", alphaOptimal, cLOptimal, cDOptimal, efficiencyOptimal);
            return;
        }
    }

    // If no matching point is found, display an error message and exit
    std::cerr << "\nERROR: Could not find optimal value." << std::endl;
    exit(1);
}