// CustomFunctions.h
#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <vector>
#include <string>
#include <utility> // For std::pair

// Function declarations

// Function to read data from the file
void readDataFromFile(const std::string& filename, std::vector<std::pair<float, float>>& data);

// Function to print n lines of data
void printData(int n, const std::vector<std::pair<float, float>>& data);

// Function to calculate the magnitude of each data point and print/save them
void calculateMagnitudes(const std::vector<std::pair<float, float>>& data);

// Function to fit a line using least squares
void fitLine(const std::vector<std::pair<float, float>>& data);

#endif // CUSTOMFUNCTIONS_H
