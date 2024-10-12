/*
    This file provides functions to interact with the xfoil airfoil analysis tool. 
    It allows opening a process to run xfoil, sending commands to it, and closing the process. 
    Xfoil is executed via a command-line interface, and this code handles the communication with xfoil 
    using pipes (standard input/output redirection).
*/

#include "../Header/control_xfoil.h"

#include <iostream>
#include <cstdio>   
#include <cstdlib>  

FILE* xfoil = nullptr;  // Global file pointer for xfoil process

// Function to open the xfoil process.
// This function opens a pipe to run the external xfoil executable.
// It uses the popen() function to start xfoil as a subprocess and redirects its output to avoid displaying it.
void openXfoil() {
    // Attempt to open xfoil as a subprocess
    xfoil = popen("xfoil.exe > nul 2>&1", "w");     // "w" indicates writing mode (sending commands to xfoil)

    // Check if the XFOIL process opened successfully
    if (xfoil == nullptr) {
        // If the process fails to open, display an error message
        std::cerr << "Error: Failed to open xfoil" << std::endl;
    }
}

// Function to send a command to xfoil.
// This function sends a command to the xfoil process by writing to the open pipe.
// The command is passed as a string and converted to C-style string (using .c_str()) before sending it.
void sendCommandToXfoil(const std::string& command) {
    if (xfoil) {    // Check if xfoil is open
        // Write the command to the xfoil process and append a newline character
        fprintf(xfoil, "%s\n", command.c_str());

        // Flush the output to ensure the command is sent immediately to xfoil
        fflush(xfoil); 
    } 
    else {
        // If xfoil is not open, print an error message
        std::cerr << "Error: xfoil is not open" << std::endl;
        exit(1);
    }
}

// Function to close the xfoil process
// This function closes the xfoil process by calling pclose(), which terminates the pipe connection.
void closeXfoil() {
    if (xfoil) {    // Check if xfoil is open
        // Close the xfoil process and reset the file pointer
        pclose(xfoil);
        xfoil = nullptr;    // Set the file pointer to null after closing
    }
}