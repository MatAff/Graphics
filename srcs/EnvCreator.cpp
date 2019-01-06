#include "EnvCreator.h"
#include <math.h>
#include "Degree.h"
#include "Triangle.h"

EnvCreator::EnvCreator() {}
EnvCreator::~EnvCreator() { }

void EnvCreator::createCircle(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        Vec c,
                        float r,
                        float height,
                        size_t nrSteps,
                        float s,
                        float e,
                        Vec color)
{
    float stepSize = (e - s) / nrSteps;
    for(size_t step = 0; step < nrSteps; ++step)
    {
        float dirDeg = s + step * stepSize;
        float rad = Degree::degToRad(dirDeg);
        float dx = sin(rad) * r;
        float dy = cos(rad) * r;
        float dirDeg2 = s + (step + 1) * stepSize;
        float rad2 = Degree::degToRad(dirDeg2);
        float dx2 = sin(rad2) * r;
        float dy2 = cos(rad2) * r;
        Vec A(c.x + dx, c.y + dy, c.z);
        Vec B(c.x + dx, c.y + dy, c.z + height);
        Vec C(c.x + dx2, c.y + dy2, c.z);
        Vec D(c.x + dx2, c.y + dy2, c.z + height);
        std::shared_ptr<Surface*> sharedptr =
            std::make_shared<Surface*>(new Triangle(A, B, C, color));
        sfVec.push_back(sharedptr);
        std::shared_ptr<Surface*> sharedptr2 =
            std::make_shared<Surface*>(new Triangle(C, B, D, color));
        sfVec.push_back(sharedptr2);
    }
}
