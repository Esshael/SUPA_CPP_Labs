#pragma once
#include "FiniteFunctions.h"

class NormalDistribution : public FiniteFunction {
public:
    NormalDistribution(double mean, double sigma, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;

private:
    double m_Mean;
    double m_Sigma;
};

class CauchyLorentzDistribution : public FiniteFunction {
public:
    CauchyLorentzDistribution(double x0, double gamma, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;

private:
    double m_X0;
    double m_Gamma;
};

class NegativeCrystalBallDistribution : public FiniteFunction {
public:
    NegativeCrystalBallDistribution(double mean, double sigma, double alpha, double n, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;

private:
    double m_Mean;
    double m_Sigma;
    double m_Alpha;
    double m_N;
};
