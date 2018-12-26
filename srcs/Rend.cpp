
#include "Vec.h"
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
    Vec pos(0, 0, 0); // View position
    Vec dir(1, 0, 0); // Directi

    // Image
    cv::Size size(640, 480);
    cv::Mat frame(size, CV_8UC3);

    // Create objects
    // TODO create objects

    // Render
    // TODO render
    
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
