/*
    This program handles configuration settings for the airfoil simulation parameters. 
    It allows the user to view and modify key parameters such as chord length, cruise speed, 
    and kinematic viscosity, and calculates the corresponding Reynolds number. 
    A menu is provided to modify these values, and the program ensures valid (positive) input for each parameter.
*/
#include "../Header/config_settings.h"

#include <iostream>
#include <limits>
#include <iomanip>

// Number of nodes along the airfoil's surface in xfoil. Used in load_airfoil.cpp
const int panelNodes = 160;             

// Simulation parameters. Used in simulate_airfoil.cpp
const int iterLimit = 100;               // Maximum number of iterations allowed in xfoil for convergence check (for each alpha)
const double alphaStart = 0.0;         // Starting angle of attack
const double alphaEnd = 10.0;           // Ending angle of attack
const double alphaIncrement = 0.5;      // Increment of alpha at each iteration

// Variables used to calculate Reynolds number
double chord = 0.2334;                    // Airfoil chord (trailing edge - leading edge)     [m]
double cruiseSpeed = 15.5;                // Drone cruise speed                               [m/s]       
double kinematicViscosity = 1.5e-5;       // Kinematic viscosity of the fluid                 [m^2/s]

double reynoldsNumber = (chord * cruiseSpeed) / kinematicViscosity;      // Reynolds number

// Function that shows current simulation parameters values
void showConfiguration() {
    std::cout << "\nCurrent Configuration:\n";
    std::cout << "  Chord: " << std::setprecision(4) << chord << " m\n";
    std::cout << std::setprecision(4) << "  Cruise Speed: " << cruiseSpeed << " m/s (" << std::setprecision(4) << (cruiseSpeed * 1.94384) << " kts)\n";
    std::cout << "  Kinematic Viscosity: " << kinematicViscosity << " m^2/s" << std::endl;
}

// Helper function to validate user input, ensuring a positive values is provided for simulation parameters
double getPositiveInput(const std::string& prompt) {
    double value;       // Variable to store user input

    while (true) {
        std::cout << prompt;    // Display the prompt asking for input
        std::cin >> value;      // Get the input value from the user
        
        // Verify that the value provided by the user is a positive number
        if (std::cin.fail() || value <= 0.0) {
            std::cin.clear();                                                       // Clear the error state in case of invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // Ignore invalid value in the input buffer
            std::cout << "\nInvalid input. Please enter a positive number.\n";      // Ask user to enter a valid positive number
        } 
        else {
            break;  // If the input is valid, exit the loop
        }
    }
    return value;   // Return the valid input
}

// Function to modify current simulation parameters values
bool modifyConfiguration() {
    showConfiguration();    // Display the current configuration
    
    int paramChoice;
    do {
        // Display the configuration modification menu
        std::cout << "\nConfiguration menu:\n";
        std::cout << "  0. Confirm Configuration\n";
        std::cout << "  1. Change Chord\n";
        std::cout << "  2. Change Cruise Speed\n";
        std::cout << "  3. Change Kinematic Viscosity\n";
        std::cout << "Choose an option: ";

        // Validate user input for paramChoice
        while (true) {
            std::cin >> paramChoice;

            // Check if input is valid (not a string or invalid number)
            if (std::cin.fail()) {
                std::cin.clear();  // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any invalid characters in the buffer
                std::cout << "Invalid input. Please enter a valid option (0-3).\n" << std::endl;
                std::cout << "Choose an option: ";
            } 
            else if (paramChoice < 0 || paramChoice > 3) {
                std::cout << "Invalid input. Please enter a valid option (0-3).\n" << std::endl;
                std::cout << "Choose an option: ";
            } 
            else {
                break; // Valid input
            }
        }

        // Process the user's input to modify the appropriate parameter
        switch (paramChoice) {
            case 0:
                std::cout << "\nConfiguration confirmed. Proceeding with execution.\n";
                return false;   // Exit configuration menu
            case 1: {
                chord = getPositiveInput("\nEnter new chord value (m): ");      // Modify chord with validation
                showConfiguration();
                break;
            }
            case 2: {
                cruiseSpeed = getPositiveInput("\nEnter new cruise speed value (m/s): ");  // Modify cruise speed with validation
                showConfiguration();
                break;
            }
            case 3: {
                kinematicViscosity = getPositiveInput("\nEnter new kinematic viscosity value (m^2/s): ");  // Modify viscosity with validation
                showConfiguration();
                break;
            }
            default:
                std::cout << "Invalid input. Please enter a valid option (0-3).\n";
                break;
        }

        // Update the Reynolds number calculation based on modified values
        reynoldsNumber = (chord * cruiseSpeed) / kinematicViscosity;

    } while (true);             // Continue displaying the menu until the user confirms
}