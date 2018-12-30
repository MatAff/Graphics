#pragma once

#include <stdio.h>
#include <sys/timeb.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


// FPS
class FPS
{
public:
    FPS(int setWaitTime);
    ~FPS();

    // Getters
    double getFPS();
    double getTimeTaken();
    long getFrameCount();
    std::string getText();

    // Update
    bool update();

private:
    int waitTime;
    int nrFrames;
    int lastTime;
    long frameCount;
    double fps;
    double timeTaken;
    int getTimeMM();
};

static FPS gFps(1000);
