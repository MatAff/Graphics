
#include "Vec.h"
#include "QuadEq.h"

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
    
}
