#include "regressioncomputer.hpp"
#include <cmath>
#include <iostream>

RegressionComputer::RegressionComputer(int features) : features_(features), alpha_(0.0000001), theta_(features)
{

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
//    applyFeatureScaling();

    const double eps = 0.000000001;

    double prev, cur;
    cur = costFunction();

    int iterations = 0;
    const int max_iterations = 200000000;

    std::valarray<double> gradient(features_);

    do
    {
        prev = cur;
        
        gradient = 0.0;

        for ( int i = 0; i < (int)training_set.size(); ++i )
            gradient += (hypothesis(training_set[i].first) - training_set[i].second) * training_set[i].first;        
/*
        std::cout << "Gradient = " << gradient << '\n';
        std::cout << "θ = " << theta_ << '\n';
*/
        theta_ -= alpha_ / training_set.size() * gradient;
/*
        std::cout << "new θ = " << theta_ << '\n';
        std::cout << "J(θ) = " << cur << '\n';
*/
        cur = costFunction();
/*
        std::cout << "new J(θ) = " << cur << '\n';

        std::cout << "|δ| = " << fabs(cur - prev) << '\n';
        std::cout << " ε  = " << eps << '\n';
        std::cout << "|δ| > ε  = " << (fabs(cur - prev) >= eps) << '\n';
*/
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

void RegressionComputer::applyFeatureScaling()
{
    std::valarray<double> mean(features_);

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

    for ( int i = 0; i < (int)training_set.size(); ++i )
        training_set[i].first = (training_set[i].first - mean) / (maximum - minimum);
}

std::ostream& operator<<(std::ostream& out, std::valarray<double> arr)
{
    for ( auto x : arr )
        out << x << ' ';
    out << '\n';
    return out;
}
