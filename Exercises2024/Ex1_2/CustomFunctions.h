#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <vector>
#include <string>
#include <utility>  // For std::pair

// Function to read data from a file (x, y pairs)
void readDataFromFile(const std::string& filename, std::vector<std::pair<float, float>>& data);

// Function to read errors from a file (expected errors for each y value)
void readErrorsFromFile(const std::string& filename, std::vector<float>& errors);

// Function to perform least squares fit and calculate χ²/NDF
void fitLineAndCalculateChiSquared(const std::vector<std::pair<float, float>>& data, 
                                    const std::vector<float>& errors, 
                                    float& chiSquared, 
                                    float& degreesOfFreedom, 
                                    std::string& lineEquation);

// Function to calculate x^y for each data point, rounding y to nearest whole number
void calculateXToThePowerY(std::vector<std::pair<float, float>>& data);

// Overloaded print functions for different types of data
void printData(const std::vector<std::pair<float, float>>& data, int n);
void printData(const std::vector<float>& magnitudes);
void printData(const std::string& lineEquation);
void printData(const float& chiSquared, const float& degreesOfFreedom);

// Function to save results to different output files
void saveResultsToFile(const std::string& filename, const std::string& content);
void saveResultsToFile(const std::string& filename, const float& chiSquared, const float& degreesOfFreedom);
void saveResultsToFile(const std::string& filename, const std::vector<std::pair<float, float>>& data);

#endif // CUSTOMFUNCTIONS_H
