#include "Distributions.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <limits>

// Load random data
std::vector<double> loadRandomData(const std::string& filename) {
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

// Calculate mean squared error
double calculateMSE(const std::vector<double>& data, FiniteFunction& function) {
    double mse = 0.0;
    for (const auto& x : data) {
        double modelValue = function.callFunction(x) / function.integral(1000);
        mse += (x - modelValue) * (x - modelValue);
    }
    return mse / data.size();
}

// Optimize parameters for Normal Distribution
void optimizeParameters(std::vector<double>& data, NormalDistribution& normal) {
    double bestMean = 0.0, bestSigma = 1.0;
    double bestError = std::numeric_limits<double>::max();

    for (double mean = -5.0; mean <= 5.0; mean += 0.1) {
        for (double sigma = 0.1; sigma <= 5.0; sigma += 0.1) {
            normal = NormalDistribution(mean, sigma, -5.0, 5.0, "NormalFit");
            double error = calculateMSE(data, normal);
            if (error < bestError) {
                bestError = error;
                bestMean = mean;
                bestSigma = sigma;
            }
        }
    }

    std::cout << "Best Fit Parameters: mean = " << bestMean
              << ", sigma = " << bestSigma
              << ", error = " << bestError << std::endl;

    normal = NormalDistribution(bestMean, bestSigma, -5.0, 5.0, "BestNormalFit");
}

int main() {
    // Load data
    std::string dataFile = "Outputs/data/MysteryData20212.txt";
    std::vector<double> randomData = loadRandomData(dataFile);

    // Candidate distributions
    NormalDistribution normal(0.0, 1.0, -5.0, 5.0, "NormalDistribution");

    // Optimize parameters
    optimizeParameters(randomData, normal);

    // Plot the fit
    normal.plotFunction();
    normal.plotData(randomData, 50);
    normal.printInfo();

    return 0;
}
