#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "Vec.h"

class Triangle
{
public:
    Triangle(Vec a, Vec b, Vec c);
    ~Triangle();

    Vec intersect(Vec eye, Vec dir);

private:
    Vec a;
    Vec b;
    Vec c;
};
