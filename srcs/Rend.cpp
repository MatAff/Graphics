#include <vector>
#include "Render.h"
#include "Vec.h"
#include "Surface.h"
#include "Sphere.h"

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

   // Create render
   Render rend(size);
   rend.render(frame, sfVec, eye, dir);

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
