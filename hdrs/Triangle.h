#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "VecD.h"
#include "Surface.h"

class Triangle : public Surface
{
public:
    Triangle(VecD a, VecD b, VecD c, VecD color);
    ~Triangle();

    VecD intersect(VecD eye, VecD dir);
    VecD normal(VecD p);

    //std::vector<float> getA() { return a.getVector(true); }
    //std::vector<float> getB() { return b.getVector(true); }
    //std::vector<float> getC() { return c.getVector(true); }

private:
    VecD a;
    VecD b;
    VecD c;
};
