#include "regressioncomputer.hpp"
#include <cmath>

RegressionComputer::RegressionComputer() : alpha(0.001)
{

}

double RegressionComputer::hypothesis(matrix<double> x) const
{
    return theta * x;
}

double RegressionComputer::costFunction() const
{
    double result = 0.0;

    for ( int i = 0; i < training_set.size(); ++i )
    {
        auto dif = hypothesis(training_set[i].first) - training_set[i].second;
        result += dif * dif;
    }

    result /= (2 * training_set.size());

    return result;
}

double RegressionComputer::gradientDescent()
{
    const double eps = 0.000001;

    matrix<double> gradient(theta.columns());

    double prev, cur;
    cur = costFunction();

    do
    {
        prev = cur;
        theta -= alpha / training_set.size() * gradient;
        cur = costFunction();
    } while ( fabs(cur - prev) >= eps );

    return cur;
}
