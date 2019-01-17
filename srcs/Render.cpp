#include "Render.h"
#include "Matrix.h"
#include "Matrix.cpp"
#include "Triangle.h"

// Constructor
Render::Render(cv::Size size) {

    // Set Lighting
    l = Vec(-1, -1, 1);
    l = l / l.len();

    // Set frame size
    this->size = size;

}

// Destructor
Render::~Render() { }

void Render::renderObjOrder(cv::Mat& frame, std::vector<std::shared_ptr<Surface*>> sfVec, Vec eye, Vec dir)
{
    // Move points such that they appear as if the camera equals the origin

    // Clear frame
    frame = cv::Scalar(0, 0, 0);

    // Rotation matrix (x, y only)
    float rad = atan(dir.x / dir.y);
    Matrix<float> R = Matrix<float>::rotateZ(-rad);
    R.print();

    // Shift matrix
    Matrix<float> S = Matrix<float>::shift(eye * -1);
    S.print();

    // Combined matrix
    Matrix<float> RS = S * R;
    RS.print();

    // Loop through objs
    for(std::shared_ptr<Surface*> sfptr : sfVec) {

       // Get surface
        Surface* sf = *sfptr;

        // Reposition points
        //std::vector<float> at = RS * ((Triangle) sf->getA());


        // Draw triangle

    }
    // End loop



}

// Render method
void Render::render(cv::Mat& frame, std::vector<std::shared_ptr<Surface*> >  sfVec, Vec eye, Vec dir)
{

    // Clear frame
    frame = cv::Scalar(0, 0, 0);

    // View frame
    Vec w = dir / -dir.len();
    Vec u = Vec(0,0,1).cross(w);
    u = u / u.len();
    Vec v = w.cross(u);

    // Loop through pixels
    for(int c = 0; c < size.width; ++c) {
        float ru = left + (right - left) * ((float)c + 0.5) / (float)size.width;
        for(int r = 0; r < size.height; ++r) {
            float rv = top - (top - bottom) * ((float)r + 0.5) / (float)size.height;
            Vec pDir = dir * distance + u * ru + v * rv;

            // Calculate intersect
            //float* minDist = nullptr;
            float minDist = 999999999;
            float dist;
            for(std::shared_ptr<Surface*> sfptr : sfVec) {
                Surface* sf = *sfptr;
                Vec res = sf->intersect(eye, pDir);
                if (res.size > 0) {
                    dist = (res - eye).len();
                    //if (!minDist || dist < *minDist) {
                    if (dist < minDist) {
                        minDist = dist;
                        Vec norm = sf->normal(res);
                        Vec color = sf->getColor();
                        Vec shade = Shading::lamb(color, l, norm);
                        frame.at<cv::Vec3b>(r, c) = cv::Vec3b(shade.x, shade.y, shade.z);
                    }
                }
            }
        }
    }
}
