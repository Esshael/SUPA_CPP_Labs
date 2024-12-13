#include "Distributions.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
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

// Calculate Sum of Squared Errors (SSE)
double calculateSSE(const std::vector<double>& data, FiniteFunction& function, int Ndiv = 1000) {
    double sse = 0.0;

    // Ensure the integral is up-to-date
    function.integral(Ndiv);

    // Compute SSE by comparing model to data
    for (double point : data) {
        double modelValue = function.callFunction(point);  // Get the model value
        sse += (modelValue - point) * (modelValue - point);  // Sum squared errors
    }

    return sse;
}

// Grid search for fitting the Normal distribution parameters
void optimizeParameters(std::vector<double>& data, NormalDistribution& normal) {
    double bestMean = -2.0;  // Starting guess
    double bestSigma = 5.0;  // Large initial guess for sigma
    double bestError = std::numeric_limits<double>::max();
    int Ndiv = 1000;  // Number of subdivisions for the integral

    // Perform grid search over a range of values for mean and sigma
    for (double mean = -10.0; mean <= 10.0; mean += 0.1) {
        for (double sigma = 0.0; sigma <= 100.0; sigma += 0.5) {
            normal = NormalDistribution(mean, sigma, -5.0, 5.0, "NormalFit");
            double error = calculateSSE(data, normal, Ndiv);
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

    // Create a Normal distribution with the optimized parameters
    normal = NormalDistribution(bestMean, bestSigma, -5.0, 5.0, "BestNormalFit");
}

int main() {
    // Load random data from file
    std::vector<double> randomData = loadRandomData("Outputs/data/MysteryData20212.txt");

    // Create the Normal distribution object
    NormalDistribution normal(0.0, 1.0, -5.0, 5.0, "NormalDistribution");

    // Perform parameter optimization to find the best fit
    optimizeParameters(randomData, normal);

    // Plot the results: fitted function and the data
    normal.plotFunction();
    normal.plotData(randomData, 50);  // 50 bins for histogram
    normal.printInfo();

    return 0;
}
