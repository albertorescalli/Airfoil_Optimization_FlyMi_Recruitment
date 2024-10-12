#ifndef CONTROL_XFOIL_H
#define CONTROL_XFOIL_H

#include <string>
#include <cstdio>

// Function to open XFOIL process using a pipe
void openXfoil();

// Function to send a command to XFOIL
void sendCommandToXfoil(const std::string& command);

// Function to close XFOIL process
void closeXfoil();

#endif // CONTROL_XFOIL_H
