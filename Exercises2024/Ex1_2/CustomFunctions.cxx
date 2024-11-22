// CustomFunctions.cxx
#include "CustomFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

// Function to read data from the file
void readDataFromFile(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream file(filename);
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
        std::stringstream ss(line);
        float x, y;
        char comma;  // To handle the comma separating x and y
        if (ss >> x >> comma >> y) {
            data.push_back({x, y});
            lineCount++;
        }
    }

    file.close();
    std::cout << "Total data points read: " << lineCount << std::endl;
}

// Function to print n lines of data
void printData(int n, const std::vector<std::pair<float, float>>& data) {
    int dataSize = data.size();
    
    if (n > dataSize) {
        std::cout << "Warning: Requested more lines than available. Printing first " << dataSize << " lines.\n";
        n = dataSize;  // Adjust to print all available lines if n is greater than the data size
    }

    for (int i = 0; i < n; ++i) {
        std::cout << "x: " << data[i].first << ", y: " << data[i].second << std::endl;
    }
}

// Function to calculate the magnitude of each data point and print/save them
void calculateMagnitudes(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> magnitudes;
    std::ofstream outFile("magnitudes.txt");

    for (const auto& point : data) {
        float x = point.first;
        float y = point.second;

        // Calculate the magnitude
        float magnitude = std::sqrt(x * x + y * y);
        
        // Print magnitude to console
        std::cout << "Magnitude of (" << x << ", " << y << ") = " << magnitude << std::endl;

        // Save magnitude to file
        outFile << magnitude << std::endl;

        magnitudes.push_back(magnitude);  // Store the magnitude in vector
    }

    outFile.close();
}

// Function to fit a line using the least squares method
void fitLine(const std::vector<std::pair<float, float>>& data) {
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int N = data.size();

    // Calculate sums required for least squares
    for (const auto& point : data) {
        float x = point.first;
        float y = point.second;
        
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
    }

    // Calculate slope (m) and intercept (b)
    float m = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
    float b = (sumY - m * sumX) / N;

    // Output fitted line equation
    std::cout << "Fitted line: y = " << m << "x + " << b << std::endl;

    // Optionally, save the fitted line to a file
    std::ofstream outFile("fitted_line.txt");
    outFile << "y = " << m << "x + " << b << std::endl;
    outFile.close();
}
