#pragma once

#include <cmath>
#include "Vec.h"

class Degree
{
public:
   Degree();
   ~Degree();
   static double degToRad(double deg);
   static double radToDeg(double rad);
   static Vec pointDirDist(Vec p, float deg, float dist);
};
