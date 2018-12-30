#pragma once

#include <cmath>
#include "Vec.h"

class Shading
{
public:
   Shading();
   ~Shading();

   static Vec lamb(Vec color, Vec l, Vec n);

   //static kd = 0.5; // Diffuse coefficient 
   
};
