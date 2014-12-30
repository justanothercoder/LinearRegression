#include "regressioncomputer.hpp"
#include <cmath>
#include <iostream>

RegressionComputer::RegressionComputer(int features) : features_(features), alpha_(0.000001), theta_(makeVectorRow<double>(features))
{

}

double RegressionComputer::hypothesis(matrix<double> x) const
{
    return (theta_ * x)(0, 0);
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
    const double eps = 0.000000000001;

    double prev, cur;
    cur = costFunction();

    int iterations = 0;
    const int max_iterations = 100000000;

    matrix<double> gradient = makeVectorRow<double>(features_);
    
    do
    {
        prev = cur;
        
        for ( int i = 0; i < features_; ++i )
            gradient(0, i) = 0;

        for ( int i = 0; i < (int)training_set.size(); ++i )
        {
            double dif = hypothesis(training_set[i].first) - training_set[i].second;
            for ( int j = 0; j < features_; ++j )            
                gradient(0, j) += dif * (training_set[i].first(j, 0));
        }

        theta_ -= alpha_ / training_set.size() * gradient;
        cur = costFunction();
    } while ( fabs(cur - prev) >= eps && iterations++ < max_iterations );

    return cur;
}
    
void RegressionComputer::addTrainingExample(matrix<double> x, double y)
{
    training_set.emplace_back(x, y);
}
    
matrix<double> RegressionComputer::theta() const
{
    return theta_;
}
