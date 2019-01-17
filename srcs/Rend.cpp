#include <vector>
#include <memory>
#include "Render.h"
#include "Vec.h"
#include "Surface.h"
#include "Sphere.h"
#include "Triangle.h"
#include "FPS.h"
#include "EnvCreator.h"

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
    //Vec eye(12500, 22500, 1500); // View position
    Vec eye(0,0,0);
    Vec dir(1, 1, 0); // Direction
    dir = dir / dir.len();
    cv::Size fov(120, 80);

    // Image
    cv::Size size(640, 480);
    //cv::Size size(320, 240);
    cv::Mat frame(size, CV_8UC3);

    // Colors
    Vec redColor(0, 0, 255);
    Vec blueColor(255, 0, 0);

    // Create objects vector
    std::vector<std::shared_ptr<Surface*> > sfVec;

    // Course
    //EnvCreator::courseAVC(sfVec);

    // Loop to create objects
    /*for(size_t i = 0; i < 1; ++i) {
        std::shared_ptr<Surface*> sharedptr =
            std::make_shared<Surface*>(new Sphere(Vec(0, 500 + i * 5, 150), 150, redColor));
        sfVec.push_back(sharedptr);
    }*/

    // Add Triangle
    std::shared_ptr<Surface*> sharedptr =
        std::make_shared<Surface*>(new Triangle(Vec(0, 500, 500),
                                                Vec(100, 500, 300),
                                                Vec(100, 500, 500), redColor));
    sfVec.push_back(sharedptr);

    // Add Surface
    /*EnvCreator::createCircle(sfVec, eye, 10, 2, 20, 90, 270, Vec(255, 0, 255));*/

    // Create render
    Render rend(size);

    // fps
    FPS fps(1000);

    // Main loop
    bool run = true;
    while ( run )
    {

        // Render
        //rend.render(frame, sfVec, eye, dir);
        rend.renderObjOrder(frame, sfVec, eye, dir);

        // Show image
        imshow("Live", frame);

        // User input
        int key = cv::waitKey(5);
        if (key == ESC_KEY) { run = false; }
        if (key == UP_KEY) { eye = eye + dir * 1000; }
        if (key == DOWN_KEY) { eye = eye - dir * 1000; }
        if (key == RIGHT_KEY) { dir = dir.rotateZ(-0.15); }
        if (key == LEFT_KEY) { dir = dir.rotateZ(0.15); }

        // fps
        if (fps.update()) { std::cout << fps.getText() << std::endl; }

    }

    return 0;

}
