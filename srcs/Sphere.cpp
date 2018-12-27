
#include "Sphere.h"
#include "QuadEq.h"

Sphere::Sphere(Vec c, float r)
{
    this->c = c;
    this->r = r;
}

Sphere::~Sphere() {}

Vec Sphere::intersect(Vec eye, Vec dir) 
{
    Vec shift = eye - c;
    float A = dir.dot(dir);
    float B = 2 * dir.dot(shift);
    float C = shift.dot(shift) - r * r;
    std::vector<float> res = QuadEq::solve(A, B, C); 
    float t = res[1];
    std::cout << t << std::endl;
    Vec p = eye + (dir * t);
    //float t = QuadEq::minPositive(res);
    return p;
}

