/*
    This program builds the Pareto front from the results of an airfoil simulation, where the
    Pareto front represents the set of points where no other points offer both a higher lift coefficient (cL)
    and better efficiency (cL/cD). 

    The function `buildParetoFront` processes the lift (cL), drag (cD), and angle of attack (alpha) values
    obtained from xfoil simulations. It compares each point to others in the dataset to determine whether it is
    Pareto optimal, meaning no other subsequent point provides a better trade-off between lift and efficiency.

    Points with invalid lift or drag values (i.e., zero) are ignored, and if a point is dominated by another
    in both lift and efficiency, it is excluded from the Pareto front. The resulting Pareto front is stored
    in a global vector of pairs (cL, efficiency).
*/

#include "../Header/store_sim_results.h"
#include "../Header/build_pareto_front.h"

#include <iostream>
#include <utility> 
#include <algorithm>

// Global vector to store the Pareto front points as pairs of (cL, cL/cD)
// The Pareto front will store points that represent optimal trade-offs between lift (cL) and efficiency (cL/cD).
    std::vector<std::pair<double, double>> paretoFront;

// Function to build the Pareto front from the given alpha, cL, and cD data.
// The Pareto front contains the set of points where no other point has both a higher lift (cL) and better efficiency (cL/cD).
void buildParetoFront(const std::vector<double>& alpha, const std::vector<double>& cL, const std::vector<double>& cD) {
    // Clear the paretoFront vector to avoid conflicts between consecutive simulations
    paretoFront.clear();
    
    // Start from the first point and check subsequent points to find Pareto optimal solutions
    size_t i = 0;

    // Loop through the list of lift and drag values
    while (i < cL.size()) {
        bool isParetoOptimal = true;        // Flag to check if the current point is Pareto optimal

        // Skip any pair (cL, cD) where both values are zero (as these points are not useful)
        if (cL[i] == 0.0 && cD[i] == 0.0) {
            i++;  // If current point is invalid, move to the next one
            continue;
        }

        // Compare the current point (i) with all subsequent points (j > i)
        for (size_t j = i + 1; j < cL.size(); ++j) {
            // If point j is better in both lift (cL) and efficiency (cL/cD), 
            // then the current point i is not Pareto optimal
            if (cL[j] > cL[i] && efficiency[j] > efficiency[i]) {
                isParetoOptimal = false;
                i = j;  // Skip to the next better point, skipping points in between i and j for improved efficiency
                break;
            }
        }

        // If the current point (i) is Pareto optimal, add it to the Pareto front
        if (isParetoOptimal) {
            paretoFront.push_back(std::make_pair(cL[i], efficiency[i]));    // Store (cL, cL/cD) in Pareto front
            i++;  // Move to the next point
        }
    }
}