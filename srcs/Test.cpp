
#include "Vec.h"
#include "QuadEq.h"
#include "Triangle.h"
#include "Sphere.h"

// Main program
int main(int argc,char ** argv)
{
    // Vector
    Vec v(1,1);
    v.print();
    std::cout << v.dot(v) << std::endl;
    std::cout << v.len() << std::endl;
    std::cout << std::endl; // White line

    // Quadratic equation
    QuadEq::solve(1, 3, -4);
    QuadEq::solve(1, 6, 9);
    std::cout << std::endl; // White line

    // Triangle
    Triangle t(Vec(0,0,0), Vec(0,1,0), Vec(0,0,1));
    std::cout << std::endl; // White line

    // Sphere
    Sphere s(Vec(0,0,0), 0.5);
    std::cout << std::endl; // White line

}
