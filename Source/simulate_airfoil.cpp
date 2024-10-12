/*
    This file defines a function to simulate an airfoil using xfoil. 
    The function sends a sequence of commands to xfoil to run a simulation based on 
    the current airfoil and configuration settings, such as Reynolds number, angle of attack (AOA), 
    and iteration limits. The results of the simulation are saved to a file for further analysis.

    Xfoil is controlled through command-line inputs, and this function automates the process 
    of setting up and running the simulation.
*/

#include "../Header/simulate_airfoil.h"
#include "../Header/control_xfoil.h"
#include "../Header/config_settings.h"

#include <iostream>

// Define the output file name where simulation results will be saved
std::string simDataFile = "sim_results.dat";    // File name to store simulation data

// Function to run the airfoil simulation in xfoil.
// This function sends a sequence of commands to xfoil to simulate an airfoil and store the results.
void runSimulation() {
    // Enter operating mode in xfoil
    sendCommandToXfoil("oper");     

    // Enable viscous flow simulation mode
    sendCommandToXfoil("visc");

    // Set Reynolds number based on global variable (defined in config_settings.h)
    sendCommandToXfoil("re");
    sendCommandToXfoil(std::to_string(reynoldsNumber));     // Send the calculated Reynolds number to XFOIL

    // Set the iteration limit for each angle of attack (alpha) during the simulation
    sendCommandToXfoil("iter " + std::to_string(iterLimit));        // Iteration limit is defined in config_settings.h

    // Enter polar accumulation mode to store simulation results
    sendCommandToXfoil("pacc");         // Start polar accumulation mode (for storing results)
    sendCommandToXfoil("");             // Confirm to start accumulation (enter key)
    sendCommandToXfoil("");             // Confirm once again (enter key)

    // Command to perform an angle of attack sweep from alphaStart to alphaEnd with a given increment
    std::string angleSweepCommand = "aseq " + std::to_string(alphaStart) + " " + std::to_string(alphaEnd) + " " + std::to_string(alphaIncrement);
    sendCommandToXfoil(angleSweepCommand.c_str());      // Send the AOA sweep command to xfoil

    // Save the polar data (simulation results) into a file
    sendCommandToXfoil("pwrt");         // Command to write polar results
    sendCommandToXfoil("Output\\" + simDataFile);    // Specify the output file name
    sendCommandToXfoil("y");            // Confirm overwrite if the file already exists

    // Return to the XFOIL main menu
    sendCommandToXfoil("");             // Go back to the main menu (enter key)
}