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

    float& operator()(const size_t& e);
    const float& operator()(const size_t& e) const;

    float dot(const Vec& other);
    Vec cross(const Vec& other);
    float len();
    Vec rotateZ(float rad);
    Vec operator-(const Vec& other);
    Vec operator+(const Vec& other);
    Vec operator*(float s);
    Vec operator/(float s);

    size_t size() const { return values.size(); }
    float x() const { return values[0]; }
    float y() const { return values[1]; }
    float z() const { return values[2]; }
    std::vector<float> getVector();

    //std::string toString();
    void print();

//private:
    std::vector<float> values;
};
