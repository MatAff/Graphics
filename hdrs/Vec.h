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
    float len();
    Vec operator-(Vec other);
    Vec operator+(Vec other);
    Vec operator*(float s);

    //std::string toString();
    void print();

private:
    short size;
    float x;
    float y;
    float z;
};
