#include "Degree.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// Constructor
Degree::Degree() { }

// Destructor
Degree::~Degree() { }

// Degree to radians
double Degree::degToRad(double deg) {
    return deg / 180 * M_PI;
}

// Radians to degrees
double Degree::radToDeg(double rad) {
    return rad / M_PI * 180;
}

