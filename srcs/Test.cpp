
#include "VecD.h"
#include "Matrix.h"
#include "Matrix.cpp"
#include "QuadEq.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>

// Main program
int main(int argc,char ** argv)
{
    // Cross product
    VecD a(10, 0, 0);
    VecD b(0, 0, 10);
    VecD w = a / a.len();
    w.print();
    VecD u = b.cross(w);
    u = u / u.len();
    u.print();
    VecD v = w.cross(u);
    v.print();

    // Quadratic equation
    std::vector<float> res = QuadEq::solve(1, 3, -4);
    std::cout << std::endl; // White line

    // Triangle
    Triangle t(VecD(0,0,0), VecD(0,1,0), VecD(0,0,1), VecD(255, 0, 0));
    std::cout << std::endl; // White line

    // Sphere intersect
    VecD eye(0, 0, 0);
    VecD dir(10, 1, 0);
    Sphere s(VecD(10, 0, 0), 2, VecD(255, 0, 0)); // Sphere with radius 2
    VecD sphereRes = s.intersect(eye, dir);
    sphereRes.print();
    std::cout << std::endl; // White line

    // Triangle intersect
    dir = VecD(2,1,1);
    Triangle t2(VecD(2, 0, 0), VecD(0, 1, 0), VecD(0, 0, 1), VecD(255, 0, 0));
    VecD triangleRes = t2.intersect(eye, dir);
    triangleRes.print();
    std::cout << std::endl; // White line



    Matrix<float> m(2,2,1.0);
    m = m + m;
    m.print();

    Matrix<int> l(1, 3, 1);
    Matrix<int> r(3, 1, 2);
    Matrix<int> mm = l*r;
    mm.print();


}
