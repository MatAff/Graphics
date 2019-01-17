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

Vec Vec::cross(Vec other)
{
    return Vec(y * other.z - z * other.y,
               z * other.x - x * other.z,
               x * other.y - y * other.x);
}

float Vec::len()
{
    return sqrt(this->dot(*this));
}

Vec Vec::rotateZ(float rad)
{
    return Vec(x * cos(rad) - y * sin(rad),
               x * sin(rad) + y * cos(rad),
               z);
}

Vec Vec::operator-(Vec other)
{
    return(Vec(x - other.x, y - other.y, z - other.z));
}

Vec Vec::operator+(Vec other)
{
    return(Vec(x + other.x, y + other.y, z + other.z));
}

Vec Vec::operator*(float s)
{
    return(Vec(x * s, y * s, z * s));
}

Vec Vec::operator/(float s)
{
    return(Vec(x / s, y / s, z / s));
}

std::vector<float> Vec::getVector(bool isPosition)
{
    std::vector<float> v;
    v.push_back(x);
    v.push_back(y);
    v.push_back(z);
    if (isPosition)  {
      v.push_back(1.0);
    } else {
      v.push_back(0.0);
    }
    return v;
}

void Vec::print()
{
   std::cout << x << " " << y;
   if (size == 3) { std::cout << " " << z; } // In case 3d vector
   std::cout << std::endl;
}
