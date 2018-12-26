
#include "Vec.h"

// Main program
int main(int argc,char ** argv)
{
    Vec v(1,1);
    v.print();
    std::cout << v.dot(v) << std::endl;
    std::cout << v.len() << std::endl;
}
