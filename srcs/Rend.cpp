#include <vector>
#include "Vec.h"
#include "Surface.h"
#include "Sphere.h"
#include "Shading.h"
//#include "QuadEq.h"
//#include "Triangle.h"

// Open CV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define ESC_KEY 27

// Main program
int main(int argc,char ** argv)
{

    // View
    Vec eye(0, 8, 0); // View position
    Vec dir(1, -0.5, 0); // Direction
    cv::Size fov(60, 40);

    // Lighting
    Vec l(-1,-1,-1);
    l = l / l.len();

    // Image
    cv::Size size(640, 480);
    cv::Mat frame(size, CV_8UC3);

    // Color
    Vec redColor(0, 0, 255);
    Vec blueColor(255, 0, 0);

    // Create objects
    std::vector<Surface*> sfVec;
    Sphere s1(Vec(15, 0, 0), 2, redColor); // Sphere with radius 2
    sfVec.push_back(&s1); 
    Sphere s2(Vec(10, 0, 0), 2, blueColor); // Sphere with radius 2
    sfVec.push_back(&s2); 
    //for(size_t i = 0; i < 10; ++i) {
        //Sphere s(Vec(10 + i * 5, 0, 0), 2); // Sphere with radius 2
        //sfVec.push_back(&s);
    //}

    // View frame
    Vec w = dir / dir.len();
    Vec u = Vec(0,0,1).cross(w);
    u = u / u.len();
    Vec v = w.cross(u); 
    float distance = 10;
    float left = -6;
    float right = 6;
    float top = 4;
    float bottom = -4; 
    // Loop through pixels
    for(int c = 0; c < size.width; ++c) {
        float ru = left + (right - left) * ((float)c + 0.5) / (float)size.width;
        for(int r = 0; r < size.height; ++r) {
            float rv = bottom + (top - bottom) * ((float)r + 0.5) / (float)size.height;
            Vec pDir = dir * distance + u * ru + v * rv;

            // Calculate intersect
            for(Surface* sf : sfVec) {
	        Vec res = sf->intersect(eye, pDir);
                if (res.size > 0) { 
                    Vec norm = sf->normal(res);
                    Vec color = sf->getColor();
                    Vec shade = Shading::lamb(color, l, norm);
                    frame.at<cv::Vec3b>(r, c) = cv::Vec3b(shade.x, shade.y, shade.z);
                }
            }
        }
    }
    
    // Main loop
    bool run = true; 
    while ( run )
    {
 
        // Show image
        imshow("Live", frame);

        // User input
        int key = cv::waitKey(5);
        if (key == ESC_KEY) { run = false; }

    }

    return 0;
  
} 
