#include "Distributions.h"
#include <random>
#include <cmath>
#include <iostream>

// Constructor
NormalDistribution::NormalDistribution(double mean, double sigma, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_Mean(mean), m_Sigma(sigma) {}

// Normal distribution function
double NormalDistribution::callFunction(double x) {
    double norm_factor = 1.0 / (m_Sigma * sqrt(2 * M_PI));
    double exponent = -0.5 * pow((x - m_Mean) / m_Sigma, 2);
    return norm_factor * exp(exponent);
}

// Print function info
void NormalDistribution::printInfo() {
    std::cout << "Normal Distribution with mean = " << m_Mean << ", sigma = " << m_Sigma << std::endl;
    FiniteFunction::printInfo();
}

std::vector<double> NormalDistribution::metropolisSample(int Nsteps, double stepSize) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);  // Uniform distribution for random values
    std::uniform_real_distribution<> uniformDist(getRangeMin(), getRangeMax());  // Use getter for xi range

    // Initial sample xi
    double xi = uniformDist(gen);
    samples.push_back(xi);  // Add the first sample

    for (int i = 1; i < Nsteps; ++i) {
        // Generate a candidate y from a normal distribution centered on xi
        std::normal_distribution<> normDist(xi, stepSize);  // Standard deviation = stepSize
        double y = normDist(gen);

        // Ensure y is within bounds using getter methods
        if (y < getRangeMin()) y = getRangeMin();
        if (y > getRangeMax()) y = getRangeMax();

        // Compute acceptance ratio A
        double A = std::min(1.0, callFunction(y) / callFunction(xi));

        // Generate random number to decide whether to accept y
        double T = dis(gen);
        if (T < A) {
            xi = y;  // Accept y as the new sample
        }

        samples.push_back(xi);  // Add the new sample
    }

    return samples;
}



// Cauchy-Lorentz Distribution
CauchyLorentzDistribution::CauchyLorentzDistribution(double x0, double gamma, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_X0(x0), m_Gamma(gamma) {}

double CauchyLorentzDistribution::callFunction(double x) {
    double norm_factor = 1.0 / (M_PI * m_Gamma);
    double denominator = 1 + pow((x - m_X0) / m_Gamma, 2);
    return norm_factor / denominator;
}

void CauchyLorentzDistribution::printInfo() {
    std::cout << "Cauchy-Lorentz Distribution with x0 = " << m_X0 << ", gamma = " << m_Gamma << std::endl;
    FiniteFunction::printInfo();
}

// Negative Crystal Ball Distribution
NegativeCrystalBallDistribution::NegativeCrystalBallDistribution(double mean, double sigma, double alpha, double n, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_Mean(mean), m_Sigma(sigma), m_Alpha(alpha), m_N(n) {}

double NegativeCrystalBallDistribution::callFunction(double x) {
    double t = (x - m_Mean) / m_Sigma;
    if (t > -m_Alpha) {
        return exp(-0.5 * t * t);
    } else {
        double A = pow(m_N / fabs(m_Alpha), m_N) * exp(-0.5 * m_Alpha * m_Alpha);
        double B = m_N / fabs(m_Alpha) - fabs(m_Alpha);
        return A * pow(B - t, -m_N);
    }
}

void NegativeCrystalBallDistribution::printInfo() {
    std::cout << "Negative Crystal Ball Distribution with mean = " << m_Mean
              << ", sigma = " << m_Sigma << ", alpha = " << m_Alpha << ", n = " << m_N << std::endl;
    FiniteFunction::printInfo();
}
