// Instruction for using in bash:
// @Esshael ➜ /workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2 (main) $ cd /workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2
// @Esshael ➜ /workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2 (main) $ g++ -std=c++11 -Wall -o AnalyseData AnalyseData.cxx CustomFunctions.cxx
// @Esshael ➜ /workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2 (main) $ ./AnalyseData

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CustomFunctions.h"

void displayMenu() {
    std::cout << "\nSelect an operation:\n";
    std::cout << "1. Print data\n";
    std::cout << "2. Calculate magnitudes\n";
    std::cout << "3. Fit a line using least squares\n";
    std::cout << "4. Calculate x^y for each data point\n";
    std::cout << "5. Save results to files\n";
    std::cout << "6. Exit\n";
}
int main() {
    std::vector<std::pair<float, float>> data;
    std::vector<float> errors;

    // Read data and errors from files
    readDataFromFile("input2D_float.txt", data);  // Read data
    readErrorsFromFile("error2D_float.txt", errors);  // Read errors

    bool continueRunning = true;
    while (continueRunning) {
        displayMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        int n;
        switch (choice) {
            case 1:
                std::cout << "Enter the number of lines to print: ";
                std::cin >> n;
                printData(data, n);  // Print data
                break;

            case 2:
                {
                    std::vector<float> magnitudes = calculateMagnitudes(data);  // Calculate magnitudes

                    // Print out the magnitudes
                    std::cout << "Calculated magnitudes:" << std::endl;
                    for (size_t i = 0; i < magnitudes.size(); ++i) {
                        std::cout << "Magnitude[" << i << "] = " << magnitudes[i] << std::endl;
                    }

                    std::cout << "Do you want to save the results? (y/n): ";
                    char save;
                    std::cin >> save;
                    if (save == 'y') {
                        saveResultsToFile(magnitudes, "magnitudes_output.txt");
                    }
                    break;
                }

            case 3:
                {
                    // Declare necessary variables
                    float chiSquared;
                    int degreesOfFreedom;
                    std::string lineEquation;

                    // Assuming 'errors' vector is already loaded from the error file
                    fitLineAndCalculateChiSquared(data, errors, chiSquared, degreesOfFreedom, lineEquation);  // Fit line and calculate chi-squared

                    std::cout << "Do you want to save the fitted line and chi-squared? (y/n): ";
                    char save;
                    std::cin >> save;
                    if (save == 'y') {
                        saveFittedLineToFile(lineEquation, "fitted_line_output.txt");
                        saveChiSquaredToFile(chiSquared, "chi_squared_output.txt");
                    }
                    break;
                }

            case 4:
                {
                    std::vector<float> xPowerYResults = calculateXPowerY(data);  // Calculate x^y

                    // Print out the results
                    std::cout << "Results of x^y:" << std::endl;
                    for (size_t i = 0; i < xPowerYResults.size(); ++i) {
                        std::cout << "x^y[" << i << "] = " << xPowerYResults[i] << std::endl;
                    }

                    std::cout << "Do you want to save the results? (y/n): ";
                    char save;
                    std::cin >> save;
                    if (save == 'y') {
                        saveResultsToFile(xPowerYResults, "x_to_y_output.txt");
                    }
                    break;
                }

            case 5:
                {
                    std::cout << "Saving all outputs...\n";
                    
                    // Save magnitudes
                    std::vector<float> magnitudes = calculateMagnitudes(data);  // Calculate magnitudes
                    saveResultsToFile(magnitudes, "magnitudes_output.txt");
                    
                    // Fit line and calculate chi-squared
                    float chiSquared;
                    int degreesOfFreedom;
                    std::string lineEquation;
                    fitLineAndCalculateChiSquared(data, errors, chiSquared, degreesOfFreedom, lineEquation);  // Fit line and calculate chi-squared
                    saveFittedLineToFile(lineEquation, "fitted_line_output.txt");
                    saveChiSquaredToFile(chiSquared, "chi_squared_output.txt");

                    // Save x^y results
                    std::vector<float> xPowerYResults = calculateXPowerY(data);  // Calculate x^y
                    saveResultsToFile(xPowerYResults, "x_to_y_output.txt");

                    std::cout << "All results have been saved to their respective files." << std::endl;
                    break;
                }

            case 6:
                continueRunning = false;
                std::cout << "Exiting program." << std::endl;
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }

        // If user selects '6', exit immediately without asking to perform another action
        if (!continueRunning) {
            break;
        }

        // Prompt for another action unless the program is set to exit
        char again;
        std::cout << "Do you want to perform another action? (y/n): ";
        std::cin >> again;
        if (again != 'y' && again != 'Y') {
            continueRunning = false;
        }
    }

    return 0;
}
