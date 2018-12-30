#pragma once

#include <stdio.h>
#include <iostream>
#include <string>


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
    Vec rotate(float xRad, float yRad, float zRad);
    Vec operator-(Vec other);
    Vec operator+(Vec other);
    Vec operator*(float s);
    Vec operator/(float s);

    //std::string toString();
    void print();

//private:
    short size = 0;
    float x;
    float y;
    float z;
};
