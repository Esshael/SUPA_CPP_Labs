#include "Distributions.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

// Helper function for generating uniform random numbers
double generateRandomUniform() {
    return static_cast<double>(rand()) / RAND_MAX;
}

// Normal Distribution Implementation
NormalDistribution::NormalDistribution(double mu, double sigma, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_mu(mu), m_sigma(sigma) {}

double NormalDistribution::callFunction(double x) {
    double norm = 1.0 / (m_sigma * std::sqrt(2 * M_PI));
    return norm * std::exp(-0.5 * std::pow((x - m_mu) / m_sigma, 2));
}

void NormalDistribution::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Normal Distribution with mu = " << m_mu << ", sigma = " << m_sigma << std::endl;
}

std::vector<double> NormalDistribution::sampleData(int nPoints, double stepSize) {
    std::vector<double> samples;
    double x = m_RMin + (m_RMax - m_RMin) * generateRandomUniform(); // Start with a random point
    for (int i = 0; i < nPoints; ++i) {
        double y = x + stepSize * (generateRandomUniform() - 0.5); // Propose new point y
        double A = std::min(callFunction(y) / callFunction(x), 1.0);
        if (generateRandomUniform() < A) {
            x = y; // Accept y
        }
        samples.push_back(x);
    }
    return samples;
}

// Cauchy-Lorentz Distribution Implementation
CauchyLorentzDistribution::CauchyLorentzDistribution(double x0, double gamma, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_x0(x0), m_gamma(gamma) {}

double CauchyLorentzDistribution::callFunction(double x) {
    double norm = 1.0 / (M_PI * m_gamma);
    return norm / (1 + std::pow((x - m_x0) / m_gamma, 2));
}

void CauchyLorentzDistribution::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Cauchy-Lorentz Distribution with x0 = " << m_x0 << ", gamma = " << m_gamma << std::endl;
}

std::vector<double> CauchyLorentzDistribution::sampleData(int nPoints, double stepSize) {
    std::vector<double> samples;
    double x = m_RMin + (m_RMax - m_RMin) * generateRandomUniform(); // Start with a random point
    for (int i = 0; i < nPoints; ++i) {
        double y = x + stepSize * (generateRandomUniform() - 0.5); // Propose new point y
        double A = std::min(callFunction(y) / callFunction(x), 1.0);
        if (generateRandomUniform() < A) {
            x = y; // Accept y
        }
        samples.push_back(x);
    }
    return samples;
}

// Negative Crystal Ball Implementation
NegativeCrystalBall::NegativeCrystalBall(double xbar, double sigma, double alpha, double n, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_xbar(xbar), m_sigma(sigma), m_alpha(alpha), m_n(n) {}

double NegativeCrystalBall::callFunction(double x) {
    double A = std::pow(m_n / std::fabs(m_alpha), m_n) * std::exp(-0.5 * m_alpha * m_alpha);
    double B = m_n / std::fabs(m_alpha) - std::fabs(m_alpha);
    double C = m_n / std::fabs(m_alpha) * 1.0 / (m_n - 1.0) * std::exp(-0.5 * m_alpha * m_alpha);
    double D = std::sqrt(M_PI / 2.0) * (1 + std::erf(m_alpha / std::sqrt(2)));

    double N = 1.0 / (m_sigma * (C + D));
    double t = (x - m_xbar) / m_sigma;

    if (t > -m_alpha) {
        return N * std::exp(-0.5 * t * t);
    } else {
        return N * A * std::pow(B - t, -m_n);
    }
}

void NegativeCrystalBall::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Negative Crystal Ball Distribution with xbar = " << m_xbar
              << ", sigma = " << m_sigma << ", alpha = " << m_alpha << ", n = " << m_n << std::endl;
}

std::vector<double> NegativeCrystalBall::sampleData(int nPoints, double stepSize) {
    std::vector<double> samples;
    double x = m_RMin + (m_RMax - m_RMin) * generateRandomUniform(); // Start with a random point
    for (int i = 0; i < nPoints; ++i) {
        double y = x + stepSize * (generateRandomUniform() - 0.5); // Propose new point y
        double A = std::min(callFunction(y) / callFunction(x), 1.0);
        if (generateRandomUniform() < A) {
            x = y; // Accept y
        }
        samples.push_back(x);
    }
    return samples;
}
