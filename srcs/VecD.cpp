#include "VecD.h"
#include <math.h>

VecD::VecD() : Vec() {}

VecD::VecD(float x, float y) : Vec(x, y)
{
    values.resize(2);
    values[0] = x;
    values[1] = y;
}

VecD::VecD(float x, float y, float z) : Vec(x, y, z)
{
    values.resize(3);
    values[0] = x;
    values[1] = y;
    values[2] = z;

}

VecD::~VecD() { }

float& VecD::operator()(const size_t& e)
{
    return values[e];
}

const float& VecD::operator()(const size_t& e) const
{
    return values[e];
}

float VecD::dot(const VecD& other)
{
   if (values.size()!=other.values.size()) { std::cerr << "VecDtor size does not match"; }
   float d;
   for (size_t i = 0; i < values.size(); ++i)
   {
       d += values[i] * other.values[i];
   }
   return d;
}

VecD VecD::cross(const VecD& other)
{
    if (values.size()!=3 || other.values.size()!=3) { std::cerr << "cross only defined for size==3"; }
    return VecD(values[1] * other.values[2]- values[2] * other.values[1],
               values[2] * other.values[0]- values[0] * other.values[2],
               values[0] * other.values[1]- values[1] * other.values[0]);
}

float VecD::len()
{
    return sqrt(this->dot(*this));
}

VecD VecD::rotateZ(float rad)
{
    if (values.size()!=3) { std::cerr << "rotateZ only defined for size==3"; }
    return VecD(values[0] * cos(rad) - values[1] * sin(rad),
               values[0] * sin(rad) + values[1] * cos(rad),
               values[2]);
}

VecD VecD::operator-(const VecD& other)
{
    if (values.size()!=other.values.size()) { std::cerr << "VecDtor size does not match"; }
    VecD r;
    r.values.resize(values.size());
    for (size_t i = 0; i < values.size(); ++i)
    {
        r.values[i] = values[i] - other.values[i];
    }
    return r;
}

VecD VecD::operator+(const VecD& other)
{
  if (values.size()!=other.values.size()) { std::cerr << "VecDtor size does not match"; }
  VecD r;
  r.values.resize(values.size());
  for (size_t i = 0; i < values.size(); ++i)
  {
      r.values[i] = values[i] + other.values[i];
  }
  return r;
}

VecD VecD::operator*(float s)
{
  VecD r;
  r.values.resize(values.size());
  for (size_t i = 0; i < values.size(); ++i)
  {
      r.values[i] = values[i] * s;
  }
  return r;
}

VecD VecD::operator/(float s)
{
  VecD r;
  r.values.resize(values.size());
  for (size_t i = 0; i < values.size(); ++i)
  {
      r.values[i] = values[i] / s;
  }
  return r;
}

std::vector<float> VecD::getVector()
{
    return values;
}

void VecD::print()
{
   for(size_t i = 0; i < values.size(); ++i)
   {
       std::cout << values[i] << " ";
   }
   std::cout << std::endl;
}
