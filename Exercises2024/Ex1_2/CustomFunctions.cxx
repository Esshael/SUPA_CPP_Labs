#include "CustomFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>  // For rounding

// Function to read data from a file (x, y pairs)
void readDataFromFile(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        float x, y;
        while (inputFile >> x >> y) {
            data.push_back(std::make_pair(x, y));
        }
        inputFile.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

// Function to read errors from a file
void readErrorsFromFile(const std::string& filename, std::vector<float>& errors) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        float error;
        while (inputFile >> error) {
            errors.push_back(error);
        }
        inputFile.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

// Function to perform least squares fit and calculate χ²/NDF
void fitLineAndCalculateChiSquared(const std::vector<std::pair<float, float>>& data, 
                                    const std::vector<float>& errors, 
                                    float& chiSquared, 
                                    float& degreesOfFreedom, 
                                    std::string& lineEquation) {
    // Perform the least squares fit: y = mx + c
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int n = data.size();

    for (int i = 0; i < n; ++i) {
        float x = data[i].first;
        float y = data[i].second;
        float error = errors[i];

        sumX += x / (error * error);
        sumY += y / (error * error);
        sumXY += x * y / (error * error);
        sumX2 += x * x / (error * error);
    }

    // Calculate slope (m) and intercept (c)
    float denominator = n * sumX2 - sumX * sumX;
    float m = (n * sumXY - sumX * sumY) / denominator;
    float c = (sumX2 * sumY - sumX * sumXY) / denominator;

    // Calculate χ² and degrees of freedom
    chiSquared = 0;
    for (int i = 0; i < n; ++i) {
        float x = data[i].first;
        float y = data[i].second;
        float error = errors[i];
        chiSquared += std::pow((y - (m * x + c)) / error, 2);
    }

    degreesOfFreedom = n - 2; // 2 parameters (m, c)

    // Prepare the line equation string
    std::stringstream ss;
    ss << "y = " << m << "x + " << c;
    lineEquation = ss.str();
}

// Function to calculate x^y for each data point, rounding y to nearest whole number
void calculateXToThePowerY(std::vector<std::pair<float, float>>& data) {
    for (auto& point : data) {
        float x = point.first;
        float y = std::round(point.second);  // Round y to nearest integer
        point.second = std::pow(x, y);  // Calculate x^y
    }
}


// Function to print various types of data
void printData(const std::vector<std::pair<float, float>>& data, int n) {
    int dataSize = data.size();

    // If n is greater than the available data points, print only the first 5 lines
    if (n > dataSize) {
        std::cout << "Warning: Requested more lines than available. Printing first " << std::min(5, dataSize) << " lines.\n";
        n = std::min(5, dataSize);  // Ensure we print a maximum of 5 lines
    }
    // Print the first n lines of (x, y) pairs
    for (int i = 0; i < n; ++i) {
        std::cout << "x: " << data[i].first << ", y: " << data[i].second << std::endl;
    }
}

// Overloaded print function for magnitudes (just a simple list of numbers)
void printData(const std::vector<float>& magnitudes) {
    for (const auto& magnitude : magnitudes) {
        std::cout << magnitude << std::endl;
    }
}

// Overloaded print function for the line equation
void printData(const std::string& lineEquation) {
    std::cout << "Fitted line equation: " << lineEquation << std::endl;
}

// Overloaded print function for χ²/NDF
void printData(const float& chiSquared, const float& degreesOfFreedom) {
    std::cout << "Chi-squared: " << chiSquared << std::endl;
    std::cout << "Degrees of freedom: " << degreesOfFreedom << std::endl;
    std::cout << "Chi-squared per degree of freedom: " << chiSquared / degreesOfFreedom << std::endl;
}

// Function to save results to a file (for different types of content)
void saveResultsToFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << content << std::endl;
        outFile.close();
        std::cout << "Results saved to " << filename << std::endl;
    } else {
        std::cerr << "Error opening file " << filename << " for writing!" << std::endl;
    }
}

// Function to save χ²/NDF results to a file
void saveResultsToFile(const std::string& filename, const float& chiSquared, const float& degreesOfFreedom) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Chi-squared: " << chiSquared << std::endl;
        outFile << "Degrees of freedom: " << degreesOfFreedom << std::endl;
        outFile << "Chi-squared per degree of freedom: " << chiSquared / degreesOfFreedom << std::endl;
        outFile.close();
        std::cout << "Results saved to " << filename << std::endl;
    } else {
        std::cerr << "Error opening file " << filename << " for writing!" << std::endl;
    }
}

// Function to save x^y results to a file
void saveResultsToFile(const std::string& filename, const std::vector<std::pair<float, float>>& data) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "x, y (rounded)" << std::endl;
        for (const auto& point : data) {
            outFile << point.first << ", " << point.second << std::endl;
        }
        outFile.close();
        std::cout << "Results saved to " << filename << std::endl;
    } else {
        std::cerr << "Error opening file " << filename << " for writing!" << std::endl;
    }
}
