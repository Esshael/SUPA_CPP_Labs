// @Esshael ➜ /workspaces/SUPA_CPP_Labs/Exercises2024/Ex3_4 (main) $ g++ -std=c++20 -o monte_carlo_pi monte_carlo_pi.cxx
// @Esshael ➜ /workspaces/SUPA_CPP_Labs/Exercises2024/Ex3_4 (main) $ ./monte_carlo_pi 1.0 100000
// Estimated value of Pi: 3.15212
// @Esshael ➜ /workspaces/SUPA_CPP_Labs/Exercises2024/Ex3_4 (main) $ ./monte_carlo_pi 1.0 10000000
// Estimated value of Pi: 3.1421792

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Function to calculate the value of pi using Monte Carlo method
double calculatePi(int n, double radius) {
    int insideCircle = 0;

    // Seed the random number generator
    std::srand(std::time(0));

    for (int i = 0; i < n; ++i) {
        // Generate a random point (x, y) within the square of side 2*radius
        double x = (2.0 * radius * rand() / double(RAND_MAX)) - radius;  // Random x coordinate within [-radius, radius]
        double y = (2.0 * radius * rand() / double(RAND_MAX)) - radius;  // Random y coordinate within [-radius, radius]

        // Check if the point is inside the circle (x^2 + y^2 <= radius^2)
        if (x * x + y * y <= radius * radius) {
            insideCircle++;
        }
    }

    // Estimate pi using the formula: pi ≈ 4 * (points_inside_circle / total_points)
    return 4.0 * insideCircle / n;
}

int main(int argc, char** argv) {
    // Check if the program received correct number of arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <radius> <number_of_random_points>" << std::endl;
        return 1;
    }

    // Parse the command line arguments
    double radius = std::stod(argv[1]);  // Convert radius to double
    int n = std::stoi(argv[2]);          // Convert number of points to integer

    // Ensure the number of points is positive
    if (n <= 0) {
        std::cerr << "Number of points must be positive!" << std::endl;
        return 1;
    }

    // Calculate the value of pi using the Monte Carlo method
    double pi_estimate = calculatePi(n, radius);

    // Output the estimated value of pi with 10 decimal places
    std::cout.precision(10);
    std::cout << "Estimated value of Pi: " << pi_estimate << std::endl;

    return 0;
}
