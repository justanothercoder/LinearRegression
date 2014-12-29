#ifndef _REGRESSIONCOMPUTER_HPP_
#define _REGRESSIONCOMPUTER_HPP_

#include <vector>
#include <utility>
#include "matrix.hpp"

class RegressionComputer
{
public:

    RegressionComputer();

    double hypothesis(matrix<double> x) const;
    double costFunction() const;

    double gradientDescent();

private:

    double alpha;
    matrix<double> theta;
    std::vector< std::pair< matrix<double>, double > > training_set;
};

#endif
