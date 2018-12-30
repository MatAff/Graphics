
#include "Sphere.h"
#include "QuadEq.h"

Sphere::Sphere(Vec c, float r, Vec color)
{
    this->c = c;
    this->r = r;
    this->color = color;
}

Sphere::~Sphere() {}

Vec Sphere::intersect(Vec eye, Vec dir) 
{
    Vec shift = eye - c;
    float A = dir.dot(dir);
    float B = 2 * dir.dot(shift);
    float C = shift.dot(shift) - r * r;
    std::vector<float> res = QuadEq::solve(A, B, C); 
    Vec v;
    if (res[0] > 0) { 
        float t = res[1];
        v = eye + (dir * t);
    }
    return v;
}

Vec Sphere::normal(Vec p)
{
   return (p - c)/(p -c).len();
}

