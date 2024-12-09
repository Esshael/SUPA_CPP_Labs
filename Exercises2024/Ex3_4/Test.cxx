#include <iostream>
#include <vector>
#include <string>
#include "Distributions.h"
#include "FiniteFunctions.h"

// Function to load mystery data
std::vector<double> loadData(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<double> data;
    double value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

// Function to test and print the best parameters for each distribution
void testDistributions() {
    std::vector<double> mysteryData = loadData("Outputs/data/MysteryData20212.txt");

    // Test Normal Distribution
    NormalDistribution normal(0.0, 1.0, -5.0, 5.0, "NormalDistribution");
    normal.integral(1000);  // Calculate the integral
    normal.plotFunction();
    normal.plotData(mysteryData, 50);
    normal.printInfo();
    std::cout << "Best Normal Distribution Parameters: mu = " << normal.m_mu << ", sigma = " << normal.m_sigma << std::endl;

    // Test Cauchy-Lorentz Distribution
    CauchyLorentzDistribution cauchy(0.0, 1.0, -5.0, 5.0, "CauchyDistribution");
    cauchy.integral(1000);  // Calculate the integral
    cauchy.plotFunction();
    cauchy.plotData(mysteryData, 50);
    cauchy.printInfo();
    std::cout << "Best Cauchy-Lorentz Distribution Parameters: x0 = " << cauchy.m_x0 << ", gamma = " << cauchy.m_gamma << std::endl;

    // Test Negative Crystal Ball Distribution
    NegativeCrystalBall crystalBall(0.0, 1.0, 1.5, 2.0, -5.0, 5.0, "NegativeCrystalBall");
    crystalBall.integral(1000);  // Calculate the integral
    crystalBall.plotFunction();
    crystalBall.plotData(mysteryData, 50);
    crystalBall.printInfo();
    std::cout << "Best Negative Crystal Ball Parameters: xbar = " << crystalBall.m_xbar 
              << ", sigma = " << crystalBall.m_sigma 
              << ", alpha = " << crystalBall.m_alpha 
              << ", n = " << crystalBall.m_n << std::endl;
}

int main() {
    testDistributions();
    return 0;
}
