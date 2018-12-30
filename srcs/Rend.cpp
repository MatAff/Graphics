#include <vector>
#include "Render.h"
#include "Vec.h"
#include "Surface.h"
#include "Sphere.h"
#include "FPS.h"

//#include "QuadEq.h"
//#include "Triangle.h"

// Open CV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define ESC_KEY 27
#define UP_KEY 82
#define DOWN_KEY 84
#define RIGHT_KEY 83
#define LEFT_KEY 81

// Main program
int main(int argc,char ** argv)
{

    // View
    Vec eye(0, 8, 0); // View position
    Vec dir(1, -0.5, 0); // Direction
    dir = dir / dir.len();
    cv::Size fov(60, 40);

    // Image
    cv::Size size(640, 480);
    //cv::Size size(320, 240);
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

    // Create render
    Render rend(size);

    // fps
    FPS fps(1000);

    // Main loop
    bool run = true;
    while ( run )
    {

        // Render
        rend.render(frame, sfVec, eye, dir);

        // Show image
        imshow("Live", frame);

        // User input
        int key = cv::waitKey(5);
        if (key == ESC_KEY) { run = false; }
        if (key == UP_KEY) { eye = eye + dir * 0.15; }
        if (key == DOWN_KEY) { eye = eye - dir * 0.5; }
        if (key == RIGHT_KEY) { dir = dir.rotateZ(-0.05); }
        if (key == LEFT_KEY) { dir = dir.rotateZ(0.05); }

        // fps
        if (fps.update()) { std::cout << fps.getText() << std::endl; }

    }

    return 0;

}
