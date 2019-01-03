#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "Vec.h"
#include "Surface.h"

class Triangle : public Surface
{
public:
    Triangle(Vec a, Vec b, Vec c, Vec color);
    ~Triangle();

    Vec intersect(Vec eye, Vec dir);
    Vec normal(Vec p);

private:
    Vec a;
    Vec b;
    Vec c;
};
