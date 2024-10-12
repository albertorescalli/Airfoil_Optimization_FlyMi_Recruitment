/*
    This file serves as the entry point for the airfoil optimization program. It orchestrates the 
    entire workflow by guiding the user through entering the airfoil coordinates file, configuring 
    simulation parameters, running simulations, and generating results.
    
    The program follows these main steps:
        1. Display a starting page with instructions
        2. Prompt the user for the airfoil coordinates file name and format the file
        3. Allow the user to modify configuration settings
        4. Load the airfoil into XFOIL, run the simulation, and store results
        5. Build a Pareto front and find the optimal configuration
        6. Write a recap of the optimization results to an output file
        7. Provide options to repeat simulations, load different airfoils, or exit the program.
 */

#include "../Header/format_airfoil.h"
#include "../Header/config_settings.h"
#include "../Header/control_xfoil.h"
#include "../Header/load_airfoil.h"
#include "../Header/simulate_airfoil.h"
#include "../Header/store_sim_results.h"
#include "../Header/build_pareto_front.h"
#include "../Header/find_optimal_config.h"
#include "../Header/generate_output.h"

#include <iostream>
#include <vector>

// Function to display the starting page with program instructions
void showStartingPage();

int main() {
    showStartingPage();         // Display the initial instructions and program title

    std::string filename;       // Variable to store the name of the airfoil coordinates file entered by the user

    int userChoice = -1;        // Variable to store the user's choice of action
    std::string input;          // Variable to store user input as a string
    bool isValidChoice = true;  // Flag to check if the user's choice is valid

    // Main loop continues until the user chooses to exit
    while(userChoice != 0) {
        // Ask user to enter the name of the file containing airfoil coordinates
        if(userChoice != 1) {   // Skip file input if user chooses to repeat the simulation
            do {
                std::cout << "\nEnter airfoil coordinates file name: ";
                std::cin >> filename;        // Get the filename from user input
            } while(!fileExists("Input/" + filename));     // Repeat asking until an existing file name is entered

            // Format the airfoil coordinates file. If formatting fails, display an error and exit
            if (!formatAirfoilFile("Input/" + filename)) {
                std::cerr << "\nERROR: Failed to format the airfoil file" << std::endl;
                return 1;       // Exit with an error status
            }
        }

        // Show current variable values and configuration menu, allowing the user to modify them
        modifyConfiguration();

        openXfoil();        // Open the xfoil simulation environment

        // Load the formatted airfoil coordinates into xfoil and configure panel nodes
        loadAirfoilToXfoil("Input/" + filename);

        // Launch simulation in xfoil for the loaded airfoil with confirmed configuration variables
        runSimulation();

        closeXfoil();       // Close xfoil after simulation completion

        // Read and store simulation values for angle of attack (alpha), lift coefficient (CL), drag coefficient (CD)
        storeSimulationResults();

        // Build the Pareto front of CL and L/D values from the simulation results
        buildParetoFront(alpha, cL, cD);

        // Find the optimal combination of CL and L/D values within the Pareto front
        findOptimalConfig();

        // Generate an output file summarizing the parameters used in the simulation and optimization results
        writeRecapFile("Input/" + filename);
        
        // Prompt user for next action
        std::cout << "\nWhat would you like to do next?\n";
        std::cout << "  0. Close the program\n";
        std::cout << "  1. Repeat simulation\n";
        std::cout << "  2. Load different airfoil\n";

        do {
            isValidChoice = true;
            std::cout << "Choose an option: ";
            std::cin >> input;    // Read user input as a string

            // Validate user input and convert it to an integer only if valid
            if (input == "0" || input == "1" || input == "2") {
                userChoice = std::stoi(input);  // Convert string input to an integer
            } 
            else {
                std::cerr << "Invalid input. Please provide a valid option (0-2).\n" << std::endl;
                isValidChoice = false;          // Invalid input, continue the loop
            }
        } while(!isValidChoice);
        
        // If the user chooses to exit, print a closing message
        if(userChoice == 0) {
            std::cout << "\nProgram closed successfully." << std::endl;
        }
    }

    return 0;       // Indicate successful execution of the program
}

// Function to display the starting page with program instructions
void showStartingPage() {
    // Display program title
    std::cout << "\n\n\t\t\t\t\t    \\-------AIRFOIL OPTIMIZATION-------/\n\n" << std::endl;

    // Provide quick instructions for the user
    std::cout << "Quick Guide:\n";
    std::cout << "  -Enter the airfoil coordinates file name (ensure it's in the 'Input' folder)\n";
    std::cout << "  -Review and, if needed, modify the variables used to calculate Reynolds number\n";
    std::cout << "  -Wait for the program to execute\n";
    std::cout << "  -Check the results in 'optimization_results.txt', located in the 'Output' folder\n";
    std::cout << "  -Move the results file to a safe location to avoid overwriting in future simulations.\n" << std::endl;
}