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

    float dot(Vec other);
    Vec cross(Vec other);
    float len();
    Vec rotateZ(float rad);
    Vec operator-(Vec other);
    Vec operator+(Vec other);
    Vec operator*(float s);
    Vec operator/(float s);

    std::vector<float> getVector(bool isPosition);

    //std::string toString();
    void print();

//private:
    short size = 0;
    float x;
    float y;
    float z;
};
