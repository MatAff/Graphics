#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

class Vec
{
public:
    Vec();
    Vec(float x, float y);
    Vec(float x, float y, float z);

    ~Vec();

    float dot(const Vec& other);
    Vec cross(const Vec& other);
    float len();
    Vec rotateZ(float rad);
    Vec operator-(const Vec& other);
    Vec operator+(const Vec& other);
    Vec operator*(float s);
    Vec operator/(float s);

    float x() const { return values[0]; }
    float y() const { return values[1]; }
    float z() const { return values[2]; }
    std::vector<float> getVector();

    //std::string toString();
    void print();

//private:
    std::vector<float> values;
};
