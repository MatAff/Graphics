
#include "Sphere.h"

Sphere::Sphere(Vec c, float r)
{
    this->c = c;
    this->r = r;
}

Sphere::~Sphere() {}

Vec Sphere::intersect(Vec ray) 
{
    return Vec(0, 0, 0); // Placeholder
}
