
#include "Sphere.h"
#include "QuadEq.h"

Sphere::Sphere(VecD c, float r, VecD color)
{
    this->c = c;
    this->r = r;
    this->color = color;
}

Sphere::~Sphere() {}

VecD Sphere::intersect(VecD eye, VecD dir)
{
    VecD shift = eye - c;
    float A = dir.dot(dir);
    float B = 2 * dir.dot(shift);
    float C = shift.dot(shift) - r * r;
    std::vector<float> res = QuadEq::solve(A, B, C);
    VecD v;
    if (res[0] > 0) {
        float t = res[1];
        if (t > 0) {
            v = eye + (dir * t);
        }
    }
    return v;
}

VecD Sphere::normal(VecD p)
{
   return (p - c)/(p -c).len();
}
