#pragma once

#include <vector>
#include <memory>
#include "Surface.h"

class EnvCreator
{
public:
    EnvCreator();
    ~EnvCreator();

static void createWall(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        VecD s,
                        VecD e,
                        float height,
                        VecD color);

static void createCircle(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        VecD c,
                        float r,
                        float height,
                        size_t nrSteps,
                        float s,
                        float e,
                        VecD color);

static void courseAVC(std::vector<std::shared_ptr<Surface*> >& sfVec);
//private:

};
