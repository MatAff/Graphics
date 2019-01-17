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

template <typename T>
Matrix<T> Matrix<T>::rotateZ(const float& rad)
{
    Matrix rot(4, 4, 0.0);
    rot(0, 0) = cos(rad);
    rot(0, 1) = -sin(rad);
    rot(1, 0) = sin(rad);
    rot(1, 1) = cos(rad);
    rot(2, 2) = 1.0;
    rot(3, 3) = 1.0;
    return rot;
}

template <typename T>
Matrix<T> Matrix<T>::identity(const size_t& size)
{
    Matrix id(size, size, 0.0);
    for(size_t i = 0; i < size; ++i)
    {
       id(i,i) = 1.0;
    }
    return id;
}

template <typename T>
Matrix<T> Matrix<T>::shift(const Vec& pos)
{
    Matrix shift = Matrix<float>::identity(4);
    shift(0,3) = pos.x();
    shift(1,3) = pos.y();
    shift(2,3) = pos.z();
    return shift;
}




















// Comment to demand white space
