
#include "Vec.h"
#include "QuadEq.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>

// Main program
int main(int argc,char ** argv)
{
    // Vector
    Vec v(1,1);
    v.print();
    std::cout << v.dot(v) << std::endl;
    std::cout << v.len() << std::endl;
    std::cout << std::endl; // White line

    // Vector subtraction
    std::cout << "Vector subtraction" << std::endl;
    Vec a(3, 1, 0);
    Vec b(1, 1, 1);
    a.print();
    b.print();
    Vec delta = a - b;
    delta.print();
    std::cout << std::endl; // White line

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

}
