
#include <math.h>
#include "QuadEq.h"

std::vector<float> QuadEq::solve(float a, float b, float c)
{
    float disc = b * b - 4 * a * c;
    std::vector<float> res;
    if (disc < 0) { 
        //std::cout << "No solutions" << std::endl;
        res.push_back(0);
    }
    if (disc == 0) {
        //std::cout << -b / (2 * a) << std::endl;
        res.push_back(1);
        res.push_back(-b / (2 * a));
    }
    if (disc > 0) { 
        float minX = (-b - sqrt(disc)) / (2 * a);
        float maxX = (-b + sqrt(disc)) / (2 * a); 
        //std::cout << minX << " " << maxX << std::endl;
        res.push_back(2);
        res.push_back(minX);
        res.push_back(maxX);
    }
    return res;
}


/*float QuadEq::minPositive(float res[])
{
    if (res[1]==1) { 
        return res[1]; 
    } else {
        if (res[1] > 0) { 
            return res[1]; 
        } else {
            return res[2];
        }
    }
}*/
