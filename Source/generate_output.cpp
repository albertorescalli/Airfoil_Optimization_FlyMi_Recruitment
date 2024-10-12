/*
    This file contains the implementation of the function to generate an optimization recap
    file that summarizes the results of an airfoil simulation. The recap includes relevant 
    parameters such as the airfoil model, chord length, cruise speed, kinematic viscosity, Reynolds number,
    and the optimal configuration values (alpha, lift coefficient CL, drag coefficient CD, and efficiency L/D).
      
    The function reads the airfoil model name from the first line of the airfoil coordinate file,
    and writes the optimization results, which have been calculated in previous steps, to the recap file.
    The output format ensures easy readability and clarity for further analysis or presentation.

    The recap is saved in a file named 'optimization_recap.txt'. If a simulation is rerun, 
    this file will be overwritten, so it is recommended to move it to a safe location to avoid loss of data.
*/

#include "../Header/generate_output.h"
#include "../Header/config_settings.h"      
#include "../Header/find_optimal_config.h"   
#include "../Header/format_airfoil.h"

#include <fstream>
#include <iostream>
#include <iomanip>

// Function to write the optimization recap file
void writeRecapFile(const std::string& airfoilFile) {
    // Read the first line from the airfoil file to get the airfoil model name
    std::string firstLine;
    readCoordinatesFromFile(airfoilFile, firstLine);

    // Open the output file to write the recap
    std::ofstream recapFile("Output/optimization_recap.txt");

    if (!recapFile) {
        // Error handling if the file cannot be opened
        std::cerr << "ERROR: Could not open 'optimization_recap.txt'" << std::endl;
        exit(1);
    }

    // Write the optimization results to the file
    recapFile << "\n--- OPTIMIZATION RESULTS ---\n\n";
    recapFile << "Airfoil model: " << firstLine << "\n\n";
    recapFile << "Parameters:\n";
    recapFile << "  -Chord: " << chord << "\n";                                     // Write chord length
    recapFile << "  -Cruise Speed: " << cruiseSpeed << "\n";                        // Write cruise speed
    recapFile << "  -Kinematic Viscosity: " << kinematicViscosity << "\n";          // Write kinematic viscosity
    recapFile << "  -Reynolds Number: " << reynoldsNumber << "\n" << std::endl;     // Write Reynolds number

    // Write the optimal values obtained from the simulation
    recapFile << "Optimal Values:\n";
    recapFile << "  -Alpha: " << std::fixed << std::setprecision(3) << alphaOptimal << "\n";              // Write optimal angle of attack
    recapFile << "  -CL: " << cLOptimal << "\n";                    // Write optimal lift coefficient
    recapFile << "  -CD: " << cDOptimal << "\n";                    // Write optimal drag coefficient
    recapFile << "  -L/D: " << efficiencyOptimal << std::endl;      // Write optimal lift-to-drag ratio

    // Notify the user that the results have been stored
    std::cout << "\nResults stored in 'optimization_recap.txt'."
                  << "\n*** Move the file to a safe location to avoid further simulations from overwriting it. ***" << std::endl;

    // Close the file after writing
    recapFile.close();
}