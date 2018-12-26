
#include "Vec.h"
#include <math.h>

Vec::Vec(float x, float y)
{
    this->x = x;
    this->y = y;
    size = 2;
}

Vec::Vec(float x, float y, float z)
{
   Vec(x, y);
   size = 3;
   this->z = z;
}

Vec::~Vec() { }

float Vec::dot(Vec other) 
{
   if (size!=other.size) { std::cerr << "Vector size does not match"; }
   return x * other.x + y * other.y + z * other.z; 
}

float Vec::len() 
{
    return sqrt(this->dot(*this));
}

void Vec::print()
{
   std::cout << x << " " << y;
   if (size == 3) { std::cout << " " << z; } // In case 3d vector
   std::cout << std::endl;
}
