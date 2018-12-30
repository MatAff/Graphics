#pragma once

#include <cmath>
#include <vector>
#include "Vec.h"
#include "Surface.h"
#include "Shading.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class Render
{
public:
   Render(cv::Size size);
   ~Render();

   void render(cv::Mat& frame, std::vector<Surface*> sfVec, Vec eye, Vec dir);

private:

    // Lighting
    Vec l;

    // View frame
    float distance = 10;
    float left = -6;
    float right = 6;
    float top = 4;
    float bottom = -4;

    // Frame
    cv::Size size;
};
