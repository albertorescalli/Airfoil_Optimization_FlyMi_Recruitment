/*
    This file defines a function to load an airfoil configuration into the xfoil tool.
    The function sends a series of commands to xfoil to load the airfoil file, adjust the 
    panel settings, and configure the number of panel nodes used in the airfoil analysis.

    xfoil is controlled through command-line inputs, and this function automates the process 
    of loading the airfoil and configuring the panel nodes for further analysis.
*/

#include "../Header/load_airfoil.h"
#include "../Header/control_xfoil.h"
#include "../Header/config_settings.h"

#include <iostream>
#include <cstdio>   
#include <cstdlib>  

// Function to load an airfoil file and configure it in xfoil.
// This function sends a sequence of commands to xfoil to load an airfoil file
// and adjust panel nodes for analysis. The commands are sent via the function sendCommandToXfoil().
void loadAirfoilToXfoil(const std::string& formattedFileName) {
    // Send the command to load the specified airfoil file in XFOIL
    sendCommandToXfoil("load " + formattedFileName);        // Load airfoil in xfoil

    // Enter the panel parameter settings in xfoil to modify panel nodes
    sendCommandToXfoil("ppar");                             // Enter panel mode
    sendCommandToXfoil("n " + std::to_string(panelNodes));  // Set the number of panel nodes (defined in config_settings.h)

    // Press "Enter" to confirm the panel settings
    sendCommandToXfoil("");                                 // Confirm changes (empty string simulates Enter key)

    // Press "Enter" again to return to the main menu
    sendCommandToXfoil("");                                 // Back to main menu
}