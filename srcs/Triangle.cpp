
#include "Triangle.h"

Triangle::Triangle(Vec a, Vec b, Vec c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

Triangle::~Triangle() {}

Vec Triangle::intersect(Vec ray) 
{
    return Vec(0, 0, 0); // Placeholder
}
