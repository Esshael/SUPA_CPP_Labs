// AnalyseData.cxx
#include <iostream>
#include <vector>
#include "CustomFunctions.h"

int main() {
    std::vector<std::pair<float, float>> data;

    // Read data from file
    readDataFromFile("input2D_float.txt", data);

    if (data.empty()) {
        std::cerr << "No data to process!" << std::endl;
        return 1;
    }

    // Ask the user which function to use
    int choice;
    std::cout << "Choose an option:\n";
    std::cout << "1. Print data\n";
    std::cout << "2. Calculate magnitudes\n";
    std::cout << "3. Fit a line to the data\n";
    std::cin >> choice;

    if (choice == 1) {
        // Ask for number of lines to print
        int n;
        std::cout << "Enter the number of lines to print: ";
        std::cin >> n;
        
        // Print data
        printData(n, data);
    } else if (choice == 2) {
        // Calculate and print magnitudes
        calculateMagnitudes(data);
    } else if (choice == 3) {
        // Fit a line to the data
        if (data.size() > 1) {
            fitLine(data);
        } else {
            std::cout << "Insufficient data to fit a line!" << std::endl;
        }
    } else {
        std::cout << "Invalid choice!" << std::endl;
    }

    return 0;
}
