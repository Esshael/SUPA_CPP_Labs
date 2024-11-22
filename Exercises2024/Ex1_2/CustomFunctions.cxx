#include "CustomFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>  // For round()

// Read data from file into a vector of pairs
void readDataFromFile(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream file(filename);  // Open the file
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    int lineCount = 0;

    // Skip the header line
    std::getline(file, line);

    // Read the data lines
    while (std::getline(file, line)) {
        std::stringstream ss(line);  // Use a stringstream to split the line
        float x, y;

        // Read x and y values, separated by comma
        char comma;  // To handle the comma separating x and y
        if (ss >> x >> comma >> y) {
            data.push_back({x, y});
            lineCount++;
        }
    }

    file.close();  // Close the file
    std::cout << "Total data points read: " << lineCount << std::endl;
}

// Function to read errors from a file
void readErrorsFromFile(const std::string& filename, std::vector<float>& errors) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening error file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        float error;
        if (ss >> error) {
            errors.push_back(error);
        }
    }

    file.close();
}


// Print data (n lines, warn if n is larger than data size)
void printData(const std::vector<std::pair<float, float>>& data, int n) {
    int dataSize = data.size();
    if (n > dataSize) {
        std::cout << "Warning: n exceeds the number of data points. Printing first " << dataSize << " lines." << std::endl;
        n = dataSize;  // Adjust to print only available data
    }
    for (int i = 0; i < n; ++i) {
        std::cout << "x: " << data[i].first << " y: " << data[i].second << std::endl;
    }
}

// Calculate magnitudes
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> magnitudes;
    for (const auto& point : data) {
        magnitudes.push_back(std::sqrt(point.first * point.first + point.second * point.second));
    }
    return magnitudes;
}

// Function to perform least squares fit and calculate χ²/NDF
void fitLineAndCalculateChiSquared(const std::vector<std::pair<float, float>>& data, 
                                    const std::vector<float>& errors, 
                                    float& chiSquared, 
                                    int& degreesOfFreedom,  // Use int for degrees of freedom
                                    std::string& lineEquation) {
    // Initialize sums for least squares calculation
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int N = data.size();  // Number of data points

    // Calculate sums required for the least squares method
    for (int i = 0; i < N; ++i) {
        float x = data[i].first;
        float y = data[i].second;
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
    }

    // Calculate slope (m) and intercept (b)
    float m = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
    float b = (sumY - m * sumX) / N;

    // Store the line equation as a string
    lineEquation = "y = " + std::to_string(m) + "x + " + std::to_string(b);

    // Calculate χ² (chi-squared)
    chiSquared = 0;
    for (int i = 0; i < N; ++i) {
        float x = data[i].first;
        float y = data[i].second;
        float error = errors[i];
        
        // Predicted value from the linear fit
        float yFit = m * x + b;

        // Calculate the residual (difference between observed and predicted values)
        float residual = (y - yFit) / error;  // normalized by the error
        chiSquared += residual * residual;    // χ² = sum((y - yFit)^2 / error^2)
    }

    // Degrees of freedom (NDF)
    degreesOfFreedom = N - 2;  // Subtract 2 because we have 2 parameters (m and b)

    // Print the result
    std::cout << "Fitted line: " << lineEquation << std::endl;
    std::cout << "Chi-squared: " << chiSquared << std::endl;
    std::cout << "Degrees of freedom: " << degreesOfFreedom << std::endl;
    std::cout << "Chi-squared per degree of freedom: " << chiSquared / degreesOfFreedom << std::endl;
}



// Calculate x^y for each data point with y rounded to nearest whole number
std::vector<float> calculateXPowerY(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> result;
    for (const auto& point : data) {
        int y_rounded = std::round(point.second);  // Round y to the nearest whole number
        float value = 1;
        for (int i = 0; i < std::abs(y_rounded); ++i) {
            value *= point.first;  // Multiply x by itself abs(y_rounded) times
        }
        if (y_rounded < 0) {
            value = 1 / value;  // If y is negative, calculate the reciprocal
        }
        result.push_back(value);
    }
    return result;
}

// Save the results (magnitudes or other data) to a file
void saveResultsToFile(const std::vector<float>& data, const std::string& filename) {
    std::ofstream file(filename);
    for (const float& value : data) {
        file << value << std::endl;
    }
    file.close();
}

// Save fitted line equation to file
void saveFittedLineToFile(const std::string& lineEquation, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << lineEquation << std::endl;
    } else {
        std::cerr << "Error opening file for saving fitted line." << std::endl;
    }
    file.close();
}

// Save chi-squared value to a file
void saveChiSquaredToFile(float chiSquared, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Chi-squared: " << chiSquared << std::endl;
    } else {
        std::cerr << "Error opening file for saving chi-squared." << std::endl;
    }
    file.close();
}
