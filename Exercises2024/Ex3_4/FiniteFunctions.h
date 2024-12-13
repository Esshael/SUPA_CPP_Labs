#pragma once
#include <string>
#include <vector>
#include "gnuplot-iostream.h"

// Forward declaration of NormalDistribution, CauchyLorentzDistribution, NegativeCrystalBallDistribution
class NormalDistribution;
class CauchyLorentzDistribution;
class NegativeCrystalBallDistribution;
class FiniteFunction {
public:
    FiniteFunction();
    FiniteFunction(double range_min, double range_max, std::string outfile);
    virtual ~FiniteFunction();

    double rangeMin();
    double rangeMax();
    double integral(int Ndiv = 1000);
    void setRangeMin(double RMin);
    void setRangeMax(double RMax);
    void setOutfile(std::string outfile);
    void plotFunction();
    void plotData(std::vector<double>& points, int NBins, bool isdata = true);
    virtual void printInfo();
    virtual double callFunction(double x);

    std::vector<std::pair<double, double>> scanFunction(int Nscan = 1000);

protected:
    double integrate(int Ndiv);
    std::vector<std::pair<double, double>> makeHist(std::vector<double>& points, int Nbins);
    void checkPath(std::string outstring);
    void generatePlot(Gnuplot& gp);

    // Getter functions for m_RMin and m_RMax
    double getRangeMin() const { return m_RMin; }
    double getRangeMax() const { return m_RMax; }

private:
    double invxsquared(double x);
    double m_RMin;
    double m_RMax;
    double m_Integral;
    int m_IntDiv = 0;
    std::string m_FunctionName;
    std::string m_OutData;
    std::string m_OutPng;
    std::vector<std::pair<double, double>> m_data;
    std::vector<std::pair<double, double>> m_samples;
    std::vector<std::pair<double, double>> m_function_scan;
    bool m_plotfunction = false;
    bool m_plotdatapoints = false;
    bool m_plotsamplepoints = false;
};
