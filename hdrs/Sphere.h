#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "VecD.h"
#include "Surface.h"

class Sphere : public Surface
{
public:
    Sphere();
    Sphere(VecD c, float r, VecD color);
    ~Sphere();

    VecD intersect(VecD eye, VecD dir);
    VecD normal(VecD p);

private:
    VecD c;
    float r;
};
