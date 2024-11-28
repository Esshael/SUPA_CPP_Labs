#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <vector>
#include <string>
#include <utility>

// Function declarations
void readDataFromFile(const std::string& filename, std::vector<std::pair<float, float>>& data);
void printData(const std::vector<std::pair<float, float>>& data, int n);
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>& data);

// Function to perform least squares fit and calculate χ²/NDF
void fitLineAndCalculateChiSquared(const std::vector<std::pair<float, float>>& data, 
                                    const std::vector<float>& errors, 
                                    float& chiSquared, 
                                    int& degreesOfFreedom,  // Pass as int
                                    std::string& lineEquation);

// Function to save the fitted line equation to a file
void saveFittedLineToFile(const std::string& lineEquation, const std::string& filename);

// Function to save chi-squared value to a file
void saveChiSquaredToFile(float chiSquared, const std::string& filename);


// Function to read errors from a file
void readErrorsFromFile(const std::string& filename, std::vector<float>& errors);


void saveResultsToFile(const std::vector<float>& data, const std::string& filename);
void calculateChiSquared(const std::vector<std::pair<float, float>>& data, const std::vector<float>& errors);  // chi-squared calculation declaration
std::vector<float> calculateXPowerY(const std::vector<std::pair<float, float>>& data);
void saveDataToFile(const std::vector<std::pair<float, float>>& data, const std::string& filename);  // Save function

#endif
