#include "Matrix.h"
#include <math.h>

template <typename T>
Matrix<T>::Matrix(size_t r, size_t c, const T& v)
{
    rows = r;
    cols = c;
    values.resize(rows);
    for(size_t i = 0; i < rows; ++i)
    {
        values[i].resize(cols, v);
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
    rows = m.rows;
    cols = m.cols;
    values = m.values;
}

template <typename T>
Matrix<T>::~Matrix()
{

}
template <typename T>
T& Matrix<T>::operator()(const size_t& r, const size_t& c)
{
    return this->values[r][c];
}

template <typename T>
const T& Matrix<T>::operator()(const size_t& r, const size_t& c) const
{
    return this->values[r][c];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& other)
{
    Matrix res(rows, cols, 0.0);

    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
        {
            res(i, j) = values[i][j] + other(i, j);
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& other)
{
    Matrix res(rows, other.cols, 0.0);

    for(size_t i = 0; i < res.rows; ++i)
    {
        for(size_t j = 0; j < res.cols; ++j)
        {
            for(size_t k = 0; k < cols; ++k)
            {
                res(i, j) += values[i][k] * other(k, j);
            }
        }
    }
    return res;
}

template <typename T>
void Matrix<T>::print()
{
    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
        {
            std::cout << values[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
