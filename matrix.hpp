#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>

template <class T>
class matrix
{
    friend std::ostream& operator<<(std::ostream& out, const matrix& m)
    {
        for ( int i = 0; i < m.rows_; ++i )
        {
            for ( int j = 0; j < m.columns_; ++j )
                out << m(i, j) << ' ';
            out << '\n';
        }
        return out;
    }

public:

    matrix(int rows, int columns) : rows_(rows), columns_(columns), elements_(allocateNew(rows, columns)) { }
    
    matrix(const matrix& other) : rows_(other.rows_), columns_(other.columns_), elements_(allocateNew(other.rows_, other.columns_))
    {
        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                elements_[i][j] = other.elements_[i][j];
        }
    }

    matrix& operator=(const matrix& other)
    {
        rows_    = other.rows_;
        columns_ = other.columns_;

        freeElements();
        elements_ = allocateNew(rows_, columns_);

        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                elements_[i][j] = other.elements_[i][j];
        }

        return *this;
    }

    matrix(matrix&& other) : rows_(other.rows_), columns_(other.columns_), elements_(other.elements_)
    {
        other.rows_ = 0;
        other.columns_ = 0;
        other.elements_ = nullptr;        
    }

    matrix& operator=(matrix&& other)
    {
        rows_     = other.rows_;
        columns_  = other.columns_;
        elements_ = other.elements_;

        other.rows_ = 0;
        other.columns_ = 0;
        other.elements_ = nullptr;        

        return *this;
    }

    ~matrix() { freeElements(); }

    T& operator()(int i, int j) { return elements_[i][j]; }
    const T& operator()(int i, int j) const { return elements_[i][j]; }

    matrix operator*(const matrix& other) const
    {
        assert(columns_ == other.rows_);

        matrix result(rows_, other.columns_);

        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < other.columns_; ++j )
            {
                for ( int k = 0; k < columns_; ++k )
                    result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
        
        return result;
    }

private:

    T** allocateNew(int rows, int columns)
    {
        T** new_matrix = new T*[rows];
        
        for ( int i = 0; i < rows; ++i ) 
            new_matrix[i] = new T[columns];

        return new_matrix;        
    }

    void freeElements()
    {
        for ( int i = 0; i < rows_; ++i )
            delete elements_[i];
        delete elements_;
    }

private:

    int rows_, columns_;
    T** elements_;
};

#endif
