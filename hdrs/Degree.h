#pragma once

#include <cmath>
#include "VecD.h"

class Degree
{
public:
   Degree();
   ~Degree();
   static double degToRad(double deg);
   static double radToDeg(double rad);
   static VecD pointDirDist(VecD p, float deg, float dist);
};
