#pragma once

#include <cmath>
#include <vector>
#include <memory>
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

   void render(cv::Mat& frame, std::vector<std::shared_ptr<Surface*>> sfVec, VecD eye, VecD dir);
   void renderObjOrder(cv::Mat& frame, std::vector<std::shared_ptr<Surface*>> sfVec, VecD eye, VecD dir);

private:

    // Lighting
    VecD l;

    // View frame
    float distance = 5;
    float left = -6;
    float right = 6;
    float top = 4;
    float bottom = -4;

    // Frame
    cv::Size size;
};
