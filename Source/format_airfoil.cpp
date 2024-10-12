/*
    This program formats airfoil coordinate data for use in XFOIL. It reads the input file containing
    airfoil coordinates, processes the points to ensure proper order for XFOIL, and saves the reformatted
    data back to the original file. The program handles the detection of upper and lower surfaces, ensures that
    no duplicate points are included (except for the trailing edge), and guarantees that the points are properly  
    ordered from trailing to leading and then again to trailing edge to the trailing edge, following the required 
    XFOIL input format.
*/

#include "../Header/format_airfoil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

// Define the < operator for the Point structure (used to sort based on x-coordinate)
bool Point::operator<(const Point& other) const {
    return x < other.x;
}

// Define the != operator for the Point structure (used to check if )
bool Point::operator!=(const Point& other) const {
    return x != other.x || y != other.y;
}

// Check if a file exists. If it doesn't, print a warning message. 
// Used to verify existence of the airfoil coordinates file name entered by the user
bool fileExists(const std::string& filename) {
    std::ifstream infile(filename);

    // If unable to find the file, warn the user with a message
    if(!infile.good()) {
        std::cerr << "\nCould not find '" << filename << "'.\nPlease ensure it is located within the 'Input' folder" << std::endl;
    }

    return infile.good();   // 
}

// Read airfoil coordinates from a file, filtering out non-relevant data
std::vector<Point> readCoordinatesFromFile(const std::string& filename, std::string& firstLine) {
    std::vector<Point> points;              // Vector to store valid coordinate points
    std::ifstream infile(filename);         // Open the file for reading
    std::string line;                       // Temporary string to store each line

    // Read the first line of the file (assuming it contains the airfoil name)
    if (std::getline(infile, firstLine)) {
        // Do nothing: first line is just stored for future use
    }

    // Read the rest of the file line by line
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        double x, y;    // Used to store each point's coordinate
        
        // Check if the line contains two numbers (to filter non-numerical lines)
        if (iss >> x >> y) {
            // Check if the two numbers are both valid coordinates numbers (if they are both less than or equal to 1)
            if (x <= 1 && y <= 1) {
                points.push_back({x, y});       // If both coordinates are valid, store them in the points vector
            }
        }
    }

    return points;  // Return the vector of all valid coordinates
}

// Overwrite original airfoil coordinates file, formatting it as follows:
// First line is the same as the original one (it is assumed to contain the airfoil's name)
// Each of the following lines contains a point's x and y coordinates, separted by a single space
void saveToFile(const std::string& filename, const std::string& firstLine, const std::vector<Point>& points) {
    std::ofstream outfile(filename);    // Open the file for writing
    
    // Write back the first line of the file (assumed to contain the airfoil's name)
    outfile << firstLine << "\n";
    
    // Write each point's x and y coordinates separated by a single space
    for (const auto& point : points) {
        outfile << point.x << " " << point.y << "\n";
    }
}

// Process the airfoil points, ensuring the upper and lower surfaces ones are correctly recognized and re-joint together
std::vector<Point> processAirfoilPoints(const std::vector<Point>& points) {
    // Check if there are enough points to process
    if (points.size() < 10) {
        std::cerr << "ERROR: Not enough coordinates to load airfoil." << std::endl;
        exit(1);    // If less than 10 points are found, exit the program
    }

    // Find the points with the minimum and maximum x-coordinates (leading and trailing edges, respectively)
    auto minMaxX = std::minmax_element(points.begin(), points.end(), 
        [](const Point& a, const Point& b) {
            return a.x < b.x;                   // Compare points by x-coordinate to find min and max x values
        });
    Point leadingEdge = *minMaxX.first;    // Point with minimum x value (leading edge)
    Point trailingEdge = *minMaxX.second;  // Point with maximum x value (trailing edge)

    // Check if upper surface points need to be reversed (x should decrease when moving from trailing to leading edge)
    bool needsReversing = (points[1].x > points[0].x);  // If the second point's x value is greater than the first one's, re-ordering is needed
                                                        // since it means they are ordered ascendently rather than descendently

    // Prepare containers for the upper and lower surfaces
    std::vector<Point> upperPart;   // Container for the upper surface points
    std::set<Point> uniqueUpper;    // A set is used to ensure unique points on the upper surface
    std::vector<Point> lowerPart;   // Container for the lower surface points
    bool isLowerSurface = false;    // Flag to indicate when we've moved to lower surface coordinates

    // Iterate over the points to classify them as part of the upper or lower surface
    for (size_t i = 0; i < points.size(); ++i) {
        // When the x-coordinate starts decreasing, we've reached lower surface coordinates,
        // assuming lower surface coordinates are already rightly ordered from leading to trailing edge in the original file
        if (i > 0 && points[i].x < points[i - 1].x && !isLowerSurface) {
            isLowerSurface = true;      // Mark that we are now processing lower surface points
        }

        // If we're on the lower surface, add the point to the lowerPart
        if (isLowerSurface) {
            lowerPart.push_back(points[i]);     // Add point to lower surface container
        } 
        else {
            // Avoid duplicating the leading edge
            if (points[i] != leadingEdge) {
                uniqueUpper.insert(points[i]);      // // Add point to upper surface set (avoiding duplicates)
            }
        }
    }

    // If the upper surface needs to be reversed (for proper xfoil ordering), reverse the points
    if (needsReversing) {
        std::vector<Point> upperTemp(uniqueUpper.begin(), uniqueUpper.end());   // Convert set to vector
        std::reverse(upperTemp.begin(), upperTemp.end());                       // Reverse the vector for correct ordering
        upperPart = std::move(upperTemp);                                       // Move reversed data to upperPart
    } 
    else {
        // If no reversal is needed, simply store the upper points in upperPart
        upperPart = std::vector<Point>(uniqueUpper.begin(), uniqueUpper.end());
    }

    // Append the lower surface points to the end of the upper surface points
    upperPart.insert(upperPart.end(), lowerPart.begin(), lowerPart.end());

    return upperPart;   // Return the combined points
}

// Function to handle the complete airfoil formatting process
bool formatAirfoilFile(const std::string& inputFilename) {
    std::string firstLine;
    
    // Step 1: Read coordinates from the input file
    std::vector<Point> points = readCoordinatesFromFile(inputFilename, firstLine);
    
    // Step 2: Process the points to format the airfoil so that xfoil can properly read the file
    std::vector<Point> processedPoints = processAirfoilPoints(points);
    
    // Step 3: Save the formatted airfoil points to the input file (overwriting it)
    saveToFile(inputFilename, firstLine, processedPoints);

    return true;
}