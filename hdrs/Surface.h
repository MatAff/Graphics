#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "VecD.h"

class Surface
{
public:
    Surface();
    ~Surface();

    virtual VecD intersect(VecD eye, VecD dir)=0;
    virtual VecD normal(VecD p)=0;
    VecD getColor();

protected:
    VecD c; // Center of shape
    VecD color;
};
