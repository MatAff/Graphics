#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "Vec.h"
#include "Surface.h"

class Sphere : public Surface
{
public:
    Sphere();
    Sphere(Vec c, float r, Vec color);
    ~Sphere();

    Vec intersect(Vec eye, Vec dir);
    Vec normal(Vec p);

private:
    Vec c;
    float r;
};
