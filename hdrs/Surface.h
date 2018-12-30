#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "Vec.h"

class Surface
{
public:
    Surface(); 
    ~Surface();

    virtual Vec intersect(Vec eye, Vec dir)=0;
    virtual Vec normal(Vec p)=0;
    Vec getColor();

protected:
    Vec c; // Center of shape
    Vec color;
};
