
#include "Triangle.h"

Triangle::Triangle(Vec a, Vec b, Vec c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

Triangle::~Triangle() {}

Vec Triangle::intersect(Vec eye, Vec dir) 
{
    float A = a.x - b.x;
    float B = a.y - b.y;
    float C = a.z - b.z;
    float D = a.x - c.x;
    float E = a.y - c.y;
    float F = a.z - c.z;
    float G = dir.x;
    float H = dir.y;
    float I = dir.z;
    float J = a.x - eye.x;
    float K = a.y - eye.y;
    float L = a.z - eye.z;
    float M = A*(E*I - H*F) + B*(G*F - D*I) + C*(D*H - E*G);
    float N = F*(A*K - J*B) + E*(J*C - A*L) + D*(B*L - K*C);
    float t = N / M;
    Vec P = eye + (dir*t);
    return P;
}
