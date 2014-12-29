#include <iostream>
#include "matrix.hpp"

int main()
{
    matrix<double> m(10, 10);

    for ( int i = 0; i < m.rows(); ++i )
        for ( int j = 0; j < m.columns(); ++j )
            m(i, j) = (i + 1) * (j + 1);

    std::cout << m << '\n';

    return 0;
}
