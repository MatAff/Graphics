
#include "FPS.h"

#include <stdio.h>
#include <sys/timeb.h>
#include <iostream>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// Constructor
FPS::FPS(int setWaitTime)
{
    waitTime = setWaitTime;
    fps = 0;
    timeTaken = 0;
    lastTime = getTimeMM();
    nrFrames = 0;
    frameCount = 0;
}

// Destructor
FPS::~FPS() { }

// Get time function
int FPS::getTimeMM()
{
      struct timespec t;
      clock_gettime(CLOCK_MONOTONIC,  &t);
      return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

// Update
bool FPS::update()
{
    nrFrames++;
    frameCount++;
    int curTime = getTimeMM();
    if(curTime - lastTime > waitTime)
    {
   	timeTaken = (curTime - lastTime) / nrFrames;
        fps = nrFrames / double(curTime - lastTime) * 1000;
        nrFrames = 0;
        lastTime = curTime;
        //std::cout << getText() << std::endl;
        return true;
    } else {
        return false;
    }
}

// Getter FPS
double FPS::getFPS()
{
    return fps;
}

// Getter time taken
double FPS::getTimeTaken()
{
    return timeTaken;
}

// Getter frame count
long FPS::getFrameCount()
{
     return frameCount;
}

// To string method
std::string FPS::getText()
{
    std::string text = "FPS: " + std::to_string((int) fps) + "; Time taken: " + std::to_string((int) timeTaken) + " ms";
    return text;
}
