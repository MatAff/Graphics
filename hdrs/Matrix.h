#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


template <typename T>
class Matrix
{
public:
    Matrix(size_t r, size_t c, const T& v);
    Matrix(const Matrix<T>& m);
    ~Matrix();

   T& operator()(const size_t& r, const size_t& c);
   const T& operator()(const size_t& r, const size_t& c) const;

    Matrix<T> operator+(Matrix other);

    void print();

    size_t rows;
    size_t cols;
    std::vector<std::vector<T> > values;

};

//#include "../srcs/Matrix.cpp"
