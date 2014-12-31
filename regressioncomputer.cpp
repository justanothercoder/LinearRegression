#include "regressioncomputer.hpp"
#include <cmath>
#include <iostream>

RegressionComputer::RegressionComputer(int features) : features_(features), alpha_(0.0001), theta_(features)
{
    mean = std::valarray<double>(features);
    deviation = std::valarray<double>(1, features);
}
    
double RegressionComputer::prediction(std::valarray<double> x) const
{
    return (theta_ * ((x - mean) / deviation)).sum();
}

double RegressionComputer::hypothesis(std::valarray<double> x) const
{
    return (theta_ * x).sum();
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
    applyFeatureScaling();

    const double eps = 0.00000000001;

    double prev, cur;
    cur = costFunction();

    std::size_t iterations = 0;
    const std::size_t max_iterations = 200000000;

    std::valarray<double> gradient(features_);

    do
    {
        prev = cur;
        
        gradient = 0.0;

        for ( int i = 0; i < (int)training_set.size(); ++i )
            gradient += (hypothesis(training_set[i].first) - training_set[i].second) * training_set[i].first;        

        theta_ -= alpha_ / training_set.size() * gradient;
        cur = costFunction();

    } while ( fabs(cur - prev) >= eps && iterations++ < max_iterations );

    std::cout << "Made " << iterations << " iterations\n";

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

void RegressionComputer::applyFeatureScaling()
{
    mean = std::valarray<double>(features_);

    for ( int j = 0; j < (int)training_set.size(); ++j )
        mean += training_set[j].first;

    mean /= training_set.size();

    std::valarray<double> maximum(features_);
    std::valarray<double> minimum(features_);    
       
    for ( int i = 0; i < features_; ++i )
    {
        maximum[i] = training_set[0].first[i];
        minimum[i] = training_set[0].first[i];
        for ( int j = 1; j < (int)training_set.size(); ++j )
        {
            maximum[i] = std::max(maximum[i], training_set[j].first[i]);
            minimum[i] = std::min(minimum[i], training_set[j].first[i]);
        }
    }

    deviation = maximum - minimum;
    deviation[0] = 1;

    for ( int i = 0; i < (int)training_set.size(); ++i )
    {
        training_set[i].first = (training_set[i].first - mean) / deviation;
        training_set[i].first[0] = 1;
    }
}

std::ostream& operator<<(std::ostream& out, std::valarray<double> arr)
{
    for ( auto x : arr )
        out << x << ' ';
    out << '\n';
    return out;
}
