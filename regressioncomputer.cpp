#include "regressioncomputer.hpp"
#include <cmath>
#include <iostream>

RegressionComputer::RegressionComputer(int features) : features_(features), alpha_(0.01), theta_(features)
{

}

double RegressionComputer::hypothesis(std::valarray<double> x) const
{
    return (theta_ * x)[0];
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
    const double eps = 0.00000001;

    double prev, cur;
    cur = costFunction();

    int iterations = 0;
    const int max_iterations = 2000000000;

    std::valarray<double> gradient(features_);

    do
    {
        prev = cur;
        
        gradient = 0.0;

        for ( int i = 0; i < (int)training_set.size(); ++i )
        {
            double dif = hypothesis(training_set[i].first) - training_set[i].second;
            
            for ( int j = 0; j < features_; ++j )            
                gradient[j] += dif * (training_set[i].first[j]);
        }

        theta_ -= alpha_ / training_set.size() * gradient;
        cur = costFunction();
    } while ( fabs(cur - prev) >= eps && iterations++ < max_iterations );

    return cur;
}
    
void RegressionComputer::addTrainingExample(std::valarray<double> x, double y)
{
    training_set.emplace_back(x, y);
}
    
std::valarray<double> RegressionComputer::theta() const
{
    return theta_;
}

std::ostream& operator<<(std::ostream& out, std::valarray<double> arr)
{
    for ( auto x : arr )
        out << x << ' ';
    out << '\n';
    return out;
}
