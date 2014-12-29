#include "regressioncomputer.hpp"
#include <cmath>

RegressionComputer::RegressionComputer(int features) : features(features), alpha(0.001), theta(features, 1)
{

}

double RegressionComputer::hypothesis(matrix<double> x) const
{
    return (theta * x)(0, 0);
}

double RegressionComputer::costFunction() const
{
    double result = 0.0;

    for ( int i = 0; i < (int)training_set.size(); ++i )
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

    matrix<double> gradient(features, 1);

    double prev, cur;
    cur = costFunction();

    do
    {
        prev = cur;
        theta = theta - alpha / training_set.size() * gradient;
        cur = costFunction();
    } while ( fabs(cur - prev) >= eps );

    return cur;
}
    
void RegressionComputer::addTrainingExample(matrix<double> x, double y)
{
    training_set.emplace_back(x, y);
}
