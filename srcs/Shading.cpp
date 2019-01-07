#include "Shading.h"

// Constructor
Shading::Shading() { }

// Destructor
Shading::~Shading() { }

Vec Shading::lamb(Vec color, Vec l, Vec n)
{
    // Lambertian
    float lmb = l.dot(n);
    if (lmb < 0) { lmb = 0; }

    // ambient
    float amb = 0.25;
    return color*(amb + ((1 - amb) * lmb));
}
