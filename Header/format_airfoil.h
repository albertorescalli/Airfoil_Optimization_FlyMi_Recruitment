#ifndef FORMAT_AIRFOIL_H
#define FORMAT_AIRFOIL_H

#include <string>
#include <vector>

// Structure to represent a 2D point
struct Point {
    double x, y;  // Coordinates of the point

    // Operator for sorting points based on x-coordinate
    bool operator<(const Point& other) const;

    // Operator for comparing two points for inequality
    bool operator!=(const Point& other) const;
};

// Function to check if a file exists
bool fileExists(const std::string& filename);

// Function to read airfoil coordinates from a file, filtering non-relevant lines
std::vector<Point> readCoordinatesFromFile(const std::string& filename, std::string& firstLine);

// Function to save processed points into a file
void saveToFile(const std::string& filename, const std::string& firstLine, const std::vector<Point>& points);

// Function to process and reorder airfoil points, separating upper and lower surfaces ones
std::vector<Point> processAirfoilPoints(const std::vector<Point>& points);

// Function to handle the complete airfoil formatting process (used to call all the other functions)
bool formatAirfoilFile(const std::string& inputFilename);

#endif // FORMAT_AIRFOIL_H