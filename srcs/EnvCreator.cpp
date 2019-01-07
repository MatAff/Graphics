#include "EnvCreator.h"
#include <math.h>
#include "Degree.h"
#include "Triangle.h"

EnvCreator::EnvCreator() {}
EnvCreator::~EnvCreator() { }

void EnvCreator::createWall(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        Vec s,
                        Vec e,
                        float height,
                        Vec color)
{
    Vec A = s;
    Vec B(s.x, s.y, s.z + height);
    Vec C = e;
    Vec D(e.x, e.y, e.z + height);
    std::shared_ptr<Surface*> sharedptr =
        std::make_shared<Surface*>(new Triangle(A, B, C, color));
    sfVec.push_back(sharedptr);
    std::shared_ptr<Surface*> sharedptr2 =
        std::make_shared<Surface*>(new Triangle(C, B, D, color));
    sfVec.push_back(sharedptr2);
}

void EnvCreator::createCircle(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        Vec c,
                        float r,
                        float height,
                        size_t nrSteps,
                        float s,
                        float e,
                        Vec color)
{
    float stepSize = (e - s) / nrSteps;
    for(size_t step = 0; step < nrSteps; ++step)
    {
        float dirDeg = s + step * stepSize;
        float rad = Degree::degToRad(dirDeg);
        float dx = sin(rad) * r;
        float dy = -cos(rad) * r;
        float dirDeg2 = s + (step + 1) * stepSize;
        float rad2 = Degree::degToRad(dirDeg2);
        float dx2 = sin(rad2) * r;
        float dy2 = -cos(rad2) * r;
        Vec A(c.x + dx, c.y + dy, c.z);
        Vec B(c.x + dx, c.y + dy, c.z + height);
        Vec C(c.x + dx2, c.y + dy2, c.z);
        Vec D(c.x + dx2, c.y + dy2, c.z + height);
        std::shared_ptr<Surface*> sharedptr =
            std::make_shared<Surface*>(new Triangle(A, B, C, color));
        sfVec.push_back(sharedptr);
        std::shared_ptr<Surface*> sharedptr2 =
            std::make_shared<Surface*>(new Triangle(C, B, D, color));
        sfVec.push_back(sharedptr2);
    }
}

void EnvCreator::courseAVC(std::vector<std::shared_ptr<Surface*> >& sfVec)
{

  /// /// /// COURSE /// /// ///

  // Setting
  float courseLength = 55000;
  float courseHeight = 25000;
  float courseWidth = 5000;
  float couresHeight = 2500;

  float cx1 = courseHeight / 2 ;
  float cx2 = courseLength - cx1;
  float cy = courseHeight / 2;
  int rInner = (courseHeight / 2) - courseWidth;
  int rOuter = courseHeight / 2;

  EnvCreator::createCircle(sfVec, Vec(cx1, cy, 0), rOuter, couresHeight, 20, 135, 405, Vec(255, 0, 255)); // Left outer
  EnvCreator::createCircle(sfVec, Vec(cx2, cy, 0), rOuter, couresHeight, 20, -45, 225, Vec(255, 0, 255)); // Right outer
  EnvCreator::createCircle(sfVec, Vec(cx1, cy, 0), rInner, couresHeight, 20, 135, 405, Vec(255, 0, 255)); // Left inner
  EnvCreator::createCircle(sfVec, Vec(cx2, cy, 0), rInner, couresHeight, 20, -45, 225, Vec(255, 0, 255)); // Right inner

  // V shapes
  Vec s, e, m;

  // Left V
  s = Degree::pointDirDist(Vec(cx1, cy, 0), 45, rInner);
  e = Degree::pointDirDist(Vec(cx1, cy, 0), 135, rInner);
  m = Vec(s.x + (e.y - s.y) / 2, s.y + (e.y - s.y) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, Vec(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, Vec(255, 0, 255));

  // Right V
  s = Degree::pointDirDist(Vec(cx2, cy, 0), 225, rInner);
  e = Degree::pointDirDist(Vec(cx2, cy, 0), 315, rInner);
  m = Vec(s.x + (e.y - s.y) / 2, s.y + (e.y - s.y) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, Vec(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, Vec(255, 0, 255));

  // Top V
  s = Degree::pointDirDist(Vec(cx2, cy, 0), 225, rOuter);
  e = Degree::pointDirDist(Vec(cx1, cy, 0), 135, rOuter);
  m = Vec(s.x + (e.x - s.x) / 2, s.y + (e.x - s.x) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, Vec(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, Vec(255, 0, 255));

  // Bottom V
  s = Degree::pointDirDist(Vec(cx1, cy, 0), 45, rOuter);
  e = Degree::pointDirDist(Vec(cx2, cy, 0), 315, rOuter);
  m = Vec(s.x + (e.x - s.x) / 2, s.y + (e.x - s.x) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, Vec(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, Vec(255, 0, 255));


}
