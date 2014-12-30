#include <iostream>
#include "matrix.hpp"
#include "regressioncomputer.hpp"

int main()
{
    RegressionComputer regression_computer(2);

    auto vec = makeVectorColumn<double>(2);
    vec(0, 0) = 1;

    vec(1, 0) = 1;
    regression_computer.addTrainingExample(vec, 1);

    vec(1, 0) = 2;
    regression_computer.addTrainingExample(vec, 2);

    vec(1, 0) = 3;
    regression_computer.addTrainingExample(vec, 3);

    std::cout << "Cost function(θ) = " << regression_computer.gradientDescent() << '\n';
    std::cout << "θ = " << regression_computer.theta() << '\n';

    for ( int i = 1; i <= 10; ++i )
    {
        vec(1, 0) = i;
        std::cout << regression_computer.hypothesis(vec) << '\n';
    }

    return 0;
}
