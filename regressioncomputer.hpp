#ifndef _REGRESSIONCOMPUTER_HPP_
#define _REGRESSIONCOMPUTER_HPP_

#include <vector>
#include <valarray>
#include <utility>
#include <iostream>

std::ostream& operator<<(std::ostream& out, std::valarray<double> arr);

class RegressionComputer
{
public:

    RegressionComputer(int features);

    double hypothesis(std::valarray<double> x) const;
    double costFunction() const;
    
    double gradientDescent();

    void addTrainingExample(std::valarray<double> x, double y);

    std::valarray<double> theta() const;

private:

    void applyFeatureScaling();

private:

    int features_;

    double alpha_;
    std::valarray<double> theta_;
    std::vector< std::pair< std::valarray<double>, double > > training_set;
};

#endif
