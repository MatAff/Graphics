
#include "Vec.h"
#include "Matrix.h"
#include "Matrix.cpp" 
#include "QuadEq.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>

// Main program
int main(int argc,char ** argv)
{
    /*// Cross product
    Vec a(10, 0, 0);
    Vec b(0, 0, 10);
    Vec w = a / a.len();
    w.print();
    Vec u = b.cross(w);
    u = u / u.len();
    u.print();
    Vec v = w.cross(u);
    v.print();

    // Quadratic equation
    std::vector<float> res = QuadEq::solve(1, 3, -4);
    std::cout << std::endl; // White line

    // Triangle
    Triangle t(Vec(0,0,0), Vec(0,1,0), Vec(0,0,1));
    std::cout << std::endl; // White line

    // Sphere intersect
    Vec eye(0, 0, 0);
    Vec dir(10, 1, 0);
    Sphere s(Vec(10, 0, 0), 2); // Sphere with radius 2
    Vec sphereRes = s.intersect(eye, dir);
    sphereRes.print();
    std::cout << std::endl; // White line

    // Triangle intersect
    dir = Vec(2,1,1);
    Triangle t2(Vec(2, 0, 0), Vec(0, 1, 0), Vec(0, 0, 1));
    Vec triangleRes = t2.intersect(eye, dir);
    triangleRes.print();
    std::cout << std::endl; // White line
    */


    Matrix<float> m(2,2,1.0);
    m = m + m;
    m.print();

    Matrix<int> l(1, 3, 1);
    Matrix<int> r(3, 1, 2);
    Matrix<int> mm = l*r;
    mm.print();


}
