#include <iostream>
#include <fstream>
#include "regressioncomputer.hpp"

int main()
{
    RegressionComputer regression_computer(4);

    std::ifstream in("dataset.txt");

    double a0, a1, a2, a3, b;
    while ( in >> a0 >> a1 >> a2 >> a3 >> b )
        regression_computer.addTrainingExample({a0, a1, a2, a3}, b);

    std::cout << "Starting gradient descent\n";

    std::cout << "Cost function(θ) = " << regression_computer.gradientDescent() << '\n';
    std::cout << "θ = " << regression_computer.theta() << '\n';

    std::ofstream out("theta.out");
    out << "θ = " << regression_computer.theta() << '\n';


    return 0;
}
