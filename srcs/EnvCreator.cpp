#include "EnvCreator.h"
#include <math.h>
#include "Degree.h"
#include "Triangle.h"

EnvCreator::EnvCreator() {}
EnvCreator::~EnvCreator() { }

void EnvCreator::createWall(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        VecD s,
                        VecD e,
                        float height,
                        VecD color)
{
    VecD A = s;
    VecD B(s.x(), s.y(), s.z() + height);
    VecD C = e;
    VecD D(e.x(), e.y(), e.z() + height);
    std::shared_ptr<Surface*> sharedptr =
        std::make_shared<Surface*>(new Triangle(A, B, C, color));
    sfVec.push_back(sharedptr);
    std::shared_ptr<Surface*> sharedptr2 =
        std::make_shared<Surface*>(new Triangle(C, B, D, color));
    sfVec.push_back(sharedptr2);
}

void EnvCreator::createCircle(std::vector<std::shared_ptr<Surface*> >& sfVec,
                        VecD c,
                        float r,
                        float height,
                        size_t nrSteps,
                        float s,
                        float e,
                        VecD color)
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
        VecD A(c.x() + dx, c.y() + dy, c.z());
        VecD B(c.x() + dx, c.y() + dy, c.z() + height);
        VecD C(c.x() + dx2, c.y() + dy2, c.z());
        VecD D(c.x() + dx2, c.y() + dy2, c.z() + height);
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

  EnvCreator::createCircle(sfVec, VecD(cx1, cy, 0), rOuter, couresHeight, 20, 135, 405, VecD(255, 0, 255)); // Left outer
  EnvCreator::createCircle(sfVec, VecD(cx2, cy, 0), rOuter, couresHeight, 20, -45, 225, VecD(255, 0, 255)); // Right outer
  EnvCreator::createCircle(sfVec, VecD(cx1, cy, 0), rInner, couresHeight, 20, 135, 405, VecD(255, 0, 255)); // Left inner
  EnvCreator::createCircle(sfVec, VecD(cx2, cy, 0), rInner, couresHeight, 20, -45, 225, VecD(255, 0, 255)); // Right inner

  // V shapes
  VecD s, e, m;

  // Left V
  s = Degree::pointDirDist(VecD(cx1, cy, 0), 45, rInner);
  e = Degree::pointDirDist(VecD(cx1, cy, 0), 135, rInner);
  m = VecD(s.x() + (e.y() - s.y()) / 2, s.y() + (e.y() - s.y()) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, VecD(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, VecD(255, 0, 255));

  // Right V
  s = Degree::pointDirDist(VecD(cx2, cy, 0), 225, rInner);
  e = Degree::pointDirDist(VecD(cx2, cy, 0), 315, rInner);
  m = VecD(s.x() + (e.y() - s.y()) / 2, s.y() + (e.y() - s.y()) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, VecD(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, VecD(255, 0, 255));

  // Top V
  s = Degree::pointDirDist(VecD(cx2, cy, 0), 225, rOuter);
  e = Degree::pointDirDist(VecD(cx1, cy, 0), 135, rOuter);
  m = VecD(s.x() + (e.x() - s.x()) / 2, s.y() + (e.x() - s.x()) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, VecD(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, VecD(255, 0, 255));

  // Bottom V
  s = Degree::pointDirDist(VecD(cx1, cy, 0), 45, rOuter);
  e = Degree::pointDirDist(VecD(cx2, cy, 0), 315, rOuter);
  m = VecD(s.x() + (e.x() - s.x()) / 2, s.y() + (e.x() - s.x()) / 2, 0);
  EnvCreator::createWall(sfVec, s, m, couresHeight, VecD(255, 0, 255));
  EnvCreator::createWall(sfVec, m, e, couresHeight, VecD(255, 0, 255));


}
