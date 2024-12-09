#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FiniteFunctions.h"

// Function to load mystery data from a file
std::vector<double> loadData(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    std::vector<double> data;
    double value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

int main() {
    // Step 1: Initialize FiniteFunction object with range [-5, 5] and output file "DefaultFunction"
    FiniteFunction myFunction(-5.0, 5.0, "DefaultFunction");

    // Step 2: Load mystery data from Outputs/data/MysteryData20212.txt
    std::string mysteryDataFile = "Outputs/data/MysteryData20212.txt";
    std::vector<double> mysteryData = loadData(mysteryDataFile);

    // Step 3: Plot the function and overlay the data points
    myFunction.plotFunction();                  // Plot the default function
    myFunction.plotData(mysteryData, 50);       // Overlay the data as a histogram with 50 bins

    // Step 4: Print information about the function
    myFunction.printInfo();

    // Notify the user about output location
    std::cout << "Plots have been generated and saved. Check the Outputs/png/ directory for results." << std::endl;

    return 0;
}
