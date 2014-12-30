#include <iostream>
#include <fstream>
#include "regressioncomputer.hpp"

int main()
{
    RegressionComputer regression_computer(2);

    std::ifstream in("dataset.txt");

    double x, y;
    while ( in >> x >> y )
        regression_computer.addTrainingExample({1, x}, y);

    std::cout << "Starting gradient descent\n";

    std::cout << "Cost function(θ) = " << regression_computer.gradientDescent() << '\n';
    std::cout << "θ = " << regression_computer.theta() << '\n';

    return 0;
}
