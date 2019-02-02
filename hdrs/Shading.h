#pragma once

#include <cmath>
#include "VecD.h"

class Shading
{
public:
   Shading();
   ~Shading();

   static VecD lamb(VecD color, VecD l, VecD n);

   //static kd = 0.5; // Diffuse coefficient

};
