#include "Distributions.h"
#include "FiniteFunctions.h"
#include <fstream>
#include <vector>
#include <iostream>

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
    // Load random data
    std::vector<double> randomData = loadRandomData("Outputs/data/MysteryData20212.txt");

    // Create distributions
    NormalDistribution normal(-2.01, 2.00, -10.0, 10.0, "NormalDistribution");
    CauchyLorentzDistribution cauchy(-0.33, 2.63, -10.0, 10.0, "CauchyDistribution");
    NegativeCrystalBallDistribution crystal(-0.33, 2.63, 9.75, 0.06, -10.0, 10.0, "CrystalDistribution");

    // Enable data plotting for random data
    normal.plotData(randomData, 50); // Enable data plotting
    cauchy.plotData(randomData, 50); // Enable data plotting
    crystal.plotData(randomData, 50); // Enable data plotting

    // Generate plots for distributions
    normal.plotFunction();
    cauchy.plotFunction();
    crystal.plotFunction();

    // Print distribution information
    normal.printInfo();
    cauchy.printInfo();
    crystal.printInfo();

    return 0;
}
