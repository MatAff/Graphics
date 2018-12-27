#include "Vec.h"
#include <math.h>

Vec::Vec() {}

Vec::Vec(float x, float y)
{
    this->x = x;
    this->y = y;
    size = 2;
}

Vec::Vec(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    size = 3;
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

Vec Vec::operator-(Vec other)
{
    this->print();
    other.print();
    return(Vec(x - other.x, y - other.y, z - other.z));
}

void Vec::print()
{
   std::cout << x << " " << y;
   if (size == 3) { std::cout << " " << z; } // In case 3d vector
   std::cout << std::endl;
}
