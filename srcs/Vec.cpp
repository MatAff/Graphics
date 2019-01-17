#include "Vec.h"
#include <math.h>

Vec::Vec() {}

Vec::Vec(float x, float y)
{
    values.resize(2);
    values[0] = x;
    values[1] = y;
}

Vec::Vec(float x, float y, float z)
{
    values.resize(3);
    values[0] = x;
    values[1] = y;
    values[2] = z;

}

Vec::~Vec() { }

float Vec::dot(const Vec& other)
{
   if (values.size()!=other.values.size()) { std::cerr << "Vector size does not match"; }
   float d;
   for (size_t i = 0; i < values.size(); ++i)
   {
       d += values[i] * other.values[i];
   }
   return d;
}

Vec Vec::cross(const Vec& other)
{
    if (values.size()!=3 || other.values.size()!=3) { std::cerr << "cross only defined for size==3"; }
    return Vec(values[1] * other.values[2]- values[2] * other.values[1],
               values[2] * other.values[0]- values[0] * other.values[2],
               values[0] * other.values[1]- values[1] * other.values[0]);
}

float Vec::len()
{
    return sqrt(this->dot(*this));
}

Vec Vec::rotateZ(float rad)
{
    if (values.size()!=3) { std::cerr << "rotateZ only defined for size==3"; }
    return Vec(values[0] * cos(rad) - values[1] * sin(rad),
               values[0] * sin(rad) + values[1] * cos(rad),
               values[2]);
}

Vec Vec::operator-(const Vec& other)
{
    if (values.size()!=other.values.size()) { std::cerr << "Vector size does not match"; }
    Vec r;
    r.values.resize(values.size());
    for (size_t i = 0; i < values.size(); ++i)
    {
        r.values[i] = values[i] - other.values[i];
    }
    return r;
}

Vec Vec::operator+(const Vec& other)
{
  if (values.size()!=other.values.size()) { std::cerr << "Vector size does not match"; }
  Vec r;
  r.values.resize(values.size());
  for (size_t i = 0; i < values.size(); ++i)
  {
      r.values[i] = values[i] + other.values[i];
  }
  return r;
}

Vec Vec::operator*(float s)
{
  Vec r;
  r.values.resize(values.size());
  for (size_t i = 0; i < values.size(); ++i)
  {
      r.values[i] = values[i] * s;
  }
  return r;
}

Vec Vec::operator/(float s)
{
  Vec r;
  r.values.resize(values.size());
  for (size_t i = 0; i < values.size(); ++i)
  {
      r.values[i] = values[i] / s;
  }
  return r;
}

std::vector<float> Vec::getVector()
{
    return values;
}

void Vec::print()
{
   for(size_t i = 0; i < values.size(); ++i)
   {
       std::cout << values[i] << " ";
   }
   std::cout << std::endl;
}
