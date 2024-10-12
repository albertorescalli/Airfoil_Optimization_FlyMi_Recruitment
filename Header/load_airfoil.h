#ifndef LOAD_AIRFOIL_H
#define LOAD_AIRFOIL_H

#include <string>

// Function to open xfoil process using a pipe
void openXfoil();

// Function to send a command to xfoil
void sendCommandToXfoil(const std::string& command);

// Function to close xfoil process
void closeXfoil();

// Function to load airfoil into xfoil and configure panel nodes
void loadAirfoilToXfoil(const std::string& formattedFileName);

#endif // LOAD_AIRFOIL_H