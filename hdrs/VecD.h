#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Vec.h"

class VecD : public Vec
{
public:
    VecD();
    VecD(float x, float y);
    VecD(float x, float y, float z);

    ~VecD();

    float& operator()(const size_t& e);
    const float& operator()(const size_t& e) const;

    float dot(const VecD& other);
    VecD cross(const VecD& other);
    float len();
    VecD rotateZ(float rad);
    VecD operator-(const VecD& other);
    VecD operator+(const VecD& other);
    VecD operator*(float s);
    VecD operator/(float s);

    float x() const { return values[0]; }
    float y() const { return values[1]; }
    float z() const { return values[2]; }
    size_t size() const { return values.size(); }

    std::vector<float> getVector();

    //std::string toString();
    void print();

//private:
    std::vector<float> values;
};
