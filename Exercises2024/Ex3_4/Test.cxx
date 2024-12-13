#include "Distributions.h"
#include "FiniteFunctions.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>

// Load random data
std::vector<double> loadRandomData(const std::string &filename) {
    std::vector<double> data;
    std::ifstream file(filename);
    double value;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    while (file >> value) {
        data.push_back(value);
    }

    file.close();
    return data;
}


int main() {
    // Load random data from file
    std::vector<double> randomData = loadRandomData("Outputs/data/MysteryData20212.txt");

    // Create the Normal distribution object
    NormalDistribution normal(-2.01, 2.00, -10.0, 10.0, "NormalDistribution");

    // Plot original data and the function
    normal.plotFunction();
    normal.plotData(randomData, 50);  // 50 bins for histogram
    normal.printInfo();

    // Generate Metropolis sampled data
    int Nsteps = 10000;
    double stepSize = 0.0005; // You can tweak this step size to see how the sampling quality changes
    std::vector<double> sampledData = normal.metropolisSample(Nsteps, stepSize);

    // Plot the function and the data generated using Metropolis sampling
    normal.plotFunction();
    normal.plotData(sampledData, 50);  // 50 bins for the sampled data
    normal.printInfo();

    return 0;
}