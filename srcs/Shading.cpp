#include "Shading.h"

// Constructor
Shading::Shading() { }

// Destructor
Shading::~Shading() { }

VecD Shading::lamb(VecD color, VecD l, VecD n)
{
    // Lambertian
    float lmb = l.dot(n);
    if (lmb < 0) { lmb = 0; }

    // ambient
    float amb = 0.25;
    return color*(amb + ((1 - amb) * lmb));
}
