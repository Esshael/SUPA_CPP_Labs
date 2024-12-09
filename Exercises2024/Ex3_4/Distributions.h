#pragma once
#include "FiniteFunctions.h"
#include <cmath>
#include <vector>

// Normal Distribution Class
class NormalDistribution : public FiniteFunction {
public:
    double m_mu, m_sigma; // Mean and Standard Deviation
public:
    NormalDistribution(double mu, double sigma, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;
    std::vector<double> sampleData(int nPoints, double stepSize); // Metropolis Sampling Method
};

// Cauchy-Lorentz Distribution Class
class CauchyLorentzDistribution : public FiniteFunction {
public:
    double m_x0, m_gamma; // Location parameter and scale parameter
public:
    CauchyLorentzDistribution(double x0, double gamma, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;
    std::vector<double> sampleData(int nPoints, double stepSize); // Metropolis Sampling Method
};

// Negative Crystal Ball Distribution Class
class NegativeCrystalBall : public FiniteFunction {
public:
    double m_xbar, m_sigma, m_alpha, m_n; // Parameters for distribution
public:
    NegativeCrystalBall(double xbar, double sigma, double alpha, double n, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;
    std::vector<double> sampleData(int nPoints, double stepSize); // Metropolis Sampling Method
};
