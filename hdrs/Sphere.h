#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "Vec.h"

class Sphere
{
public:
    Sphere(Vec c, float r); 
    ~Sphere();

    Vec intersect(Vec eye, Vec dir);

private:
    Vec c;
    float r;
};