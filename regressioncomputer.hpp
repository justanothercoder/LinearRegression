#ifndef _REGRESSIONCOMPUTER_HPP_
#define _REGRESSIONCOMPUTER_HPP_

#include <vector>
#include <utility>
#include "matrix.hpp"

class RegressionComputer
{
public:

    RegressionComputer(int features);

    double hypothesis(matrix<double> x) const;
    double costFunction() const;

    double gradientDescent();

    void addTrainingExample(matrix<double> x, double y);

    matrix<double> theta() const;

private:

    int features_;

    double alpha_;
    matrix<double> theta_;
    std::vector< std::pair< matrix<double>, double > > training_set;
};

#endif
