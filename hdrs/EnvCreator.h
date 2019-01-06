#pragma once

#include <vector>
#include <memory>
#include "Surface.h"

class EnvCreator
{
public:
    EnvCreator();
    ~EnvCreator();

static void createCircle(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        Vec c,
                        float r,
                        float height,
                        size_t nrSteps,
                        float s,
                        float e,
                        Vec color);

//private:

};
