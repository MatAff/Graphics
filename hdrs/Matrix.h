#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "VecD.h"

// Derived from: https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File

template <typename T>
class Matrix
{
public:
    Matrix(size_t r, size_t c, const T& v);
    Matrix(const Matrix<T>& m);
    ~Matrix();

   T& operator()(const size_t& r, const size_t& c);
   const T& operator()(const size_t& r, const size_t& c) const;

    Matrix<T> operator+(Matrix<T>& other);
    Matrix<T> operator*(Matrix<T>& other);

    std::vector<float> operator*(std::vector<float> v);

    void print();

    static Matrix<T> rotateZ(const float& rad);
    static Matrix<T> identity(const size_t& size);
    static Matrix<T> shift(const VecD& pos);

    size_t rows;
    size_t cols;
    std::vector<std::vector<T> > values;

};

//#include "../srcs/Matrix.cpp"
