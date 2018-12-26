
#include <math.h>
#include "QuadEq.h"

void QuadEq::solve(float a, float b, float c)
{
    float disc = b * b - 4 * a * c;
    if (disc < 0) { 
        std::cout << "No solutions" << std::endl;
        return;
    }
    if (disc == 0) {
        std::cout << -b / (2 * a) << std::endl;
        return;
    }
    if (disc > 0) { 
        float minX = (-b - sqrt(disc)) / (2 * a);
        float maxX = (-b + sqrt(disc)) / (2 * a); 
        std::cout << minX << " " << maxX << std::endl;
        return;
    }
}
