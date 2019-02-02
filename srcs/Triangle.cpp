
#include "Triangle.h"

Triangle::Triangle(VecD a, VecD b, VecD c, VecD color)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->color = color;
}

Triangle::~Triangle() {}

VecD Triangle::intersect(VecD eye, VecD dir)
{
    float A = a.x() - b.x();
    float B = a.y() - b.y();
    float C = a.z() - b.z();
    float D = a.x() - c.x();
    float E = a.y() - c.y();
    float F = a.z() - c.z();
    float G = dir.x();
    float H = dir.y();
    float I = dir.z();
    float J = a.x() - eye.x();
    float K = a.y() - eye.y();
    float L = a.z() - eye.z();
    float M = A*(E*I - H*F) + B*(G*F - D*I) + C*(D*H - E*G);

    float beta = J*(E*I - H*F) + K*(G*F - D*I) + L*(D*H - E*G);
    beta = beta / M;

    float gamma = I*(A*K - J*B) + H*(J*C - A*L) + G*(B*L - K*C);
    gamma = gamma / M;

    float T = -1 * (F*(A*K - J*B) + E*(J*C - A*L) + D*(B*L - K*C));
    T = T / M;

    VecD p;
    if (beta > 0 && beta < 1 - gamma && gamma > 0 && gamma < 1 && T > 0) {
        p = eye + (dir*T);
    }
    return p;
}

VecD Triangle::normal(VecD p)
{
    VecD n = (a - b).cross(a - c);
    n = n / n.len();
    return(n);
}
