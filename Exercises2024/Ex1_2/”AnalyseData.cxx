#include <iostream>
#include <fstream> // For file input/output
#include <string>  // For working with strings

#include <iostream>
#include <fstream>
#include <vector>
#include <utility> // For std::pair

int main() {
    std::ifstream inputFile("input2D_float.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open file 'input2D float.txt'. Please check the file path and permissions." << std::endl;
        return 1;
    }

    // Vector of pairs to hold (x, y) coordinates
    std::vector<std::pair<float, float>> data;

    float x, y;
    while (inputFile >> x >> y) {
        data.emplace_back(x, y); // Store each (x, y) pair in the vector
    }

    inputFile.close();

    // Print the data from the vector
    std::cout << "Contents of 'input2D float.txt' (from data structure):" << std::endl;
    for (const auto& point : data) {
        std::cout << "(" << point.first << ", " << point.second << ")" << std::endl;
    }

    return 0;
}
