#include <iostream>
#include <vector>
#include <string>
#include "CustomFunctions.h"

int main() {
    // Declare necessary variables
    std::vector<std::pair<float, float>> data;  // To store (x, y) data pairs
    std::vector<float> errors;                  // To store errors for each y value
    float chiSquared = 0;
    float degreesOfFreedom = 0;
    std::string lineEquation;

    // 1. Read data from files
    std::string dataFile = "input2D_float.txt";  // Update with your actual file path
    std::string errorFile = "error2D_float.txt"; // Update with your actual error file path
    readDataFromFile(dataFile, data);
    readErrorsFromFile(errorFile, errors);

    // 2. Perform Least Squares Fit and calculate Chi-squared
    fitLineAndCalculateChiSquared(data, errors, chiSquared, degreesOfFreedom, lineEquation);

    // 3. Print out the results
    std::cout << "Fitting Results:" << std::endl;
    printData(lineEquation); // Print the fitted line equation
    printData(chiSquared, degreesOfFreedom); // Print the Chi-squared and Degrees of Freedom

    // 4. Save results to output files
    saveResultsToFile("fitted_line.txt", lineEquation);  // Save fitted line equation
    saveResultsToFile("chi_squared.txt", chiSquared, degreesOfFreedom); // Save chi-squared results

    // 5. Optionally calculate x^y for each data point
    calculateXToThePowerY(data);

    // 6. Print x^y results (optional)
    std::cout << "\nCalculated x^y (with y rounded to the nearest whole number):" << std::endl;
    printData(data, data.size()); // Print modified data with x^y calculation

    // 7. Save x^y results to file
    saveResultsToFile("x_to_the_power_y.txt", data);

    return 0;
}

