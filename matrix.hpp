#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <cassert>

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

    friend matrix operator*(T alpha, const matrix& m)
    {
        matrix result = m;

        for ( int i = 0; i < m.rows_; ++i )
        {
            for ( int j = 0; j < m.columns_; ++j )
                result(i, j) *= alpha;
        }

        return result;
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

    matrix operator+(const matrix& other) const
    {
        assert(rows_ == other.rows_ && columns_ == other.columns_);

        matrix result(rows_, columns_);

        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                result(i, j) = (*this)(i, j) + other(i, j);
        }

        return result;
    }
    
    matrix operator-() const
    {
        matrix result(rows_, columns_);

        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                result(i, j) = -(*this)(i, j);
        }

        return result;
    }

    matrix operator-(const matrix& other) const
    {
        return (*this) + (-other);
    }

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

    matrix operator*(T alpha)
    {
        matrix result = *this;

        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                result(i, j) *= alpha;
        }

        return result;
    }

    matrix& operator+=(const matrix& other)
    {
        assert(rows_ == other.rows_ && columns_ == other.columns_);

        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                (*this)(i, j) += other(i, j);
        }

        return *this;
    }
    
    matrix& operator-=(const matrix& other)
    {
        assert(rows_ == other.rows_ && columns_ == other.columns_);

        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                (*this)(i, j) -= other(i, j);
        }

        return *this;
    }

    int rows() const { return rows_; }
    int columns() const { return columns_; }

    matrix transpose() const
    {
        matrix result(columns_, rows_);
        
        for ( int i = 0; i < rows_; ++i )
        {
            for ( int j = 0; j < columns_; ++j )
                result(j, i) = (*this)(i, j);
        }

        return result;
    }

    static matrix identity(int size)
    {
        matrix result(size, size);
        for ( int i = 0; i < size; ++i )
            result(i, i) = 1;
        return result;
    }

private:

    T** allocateNew(int rows, int columns)
    {
        T** new_matrix = new T*[rows];
        
        for ( int i = 0; i < rows; ++i ) 
        {
            new_matrix[i] = new T[columns];
            for ( int j = 0; j < columns; ++j )
                new_matrix[i][j] = T();
        }

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

template <class T>
matrix<T> makeVectorRow(int length) { return matrix<T>(1, length); }

template <class T>
matrix<T> makeVectorColumn(int length) { return matrix<T>(length, 1); }

#endif
