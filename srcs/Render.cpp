#include "Render.h"

// Constructor
Render::Render(cv::Size size) {

    // Set Lighting
    l = Vec(-1,-1,-1);
    l = l / l.len();

    // Set frame size
    this->size = size;

}

// Destructor
Render::~Render() { }

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
            float rv = bottom + (top - bottom) * ((float)r + 0.5) / (float)size.height;
            Vec pDir = dir * distance + u * ru + v * rv;

            // Calculate intersect
            for(std::shared_ptr<Surface*> sfptr : sfVec) {
                Surface* sf = *sfptr;
                Vec res = sf->intersect(eye, pDir);
                if (res.size > 0) {
                    Vec norm = sf->normal(res);
                    Vec color = sf->getColor();
                    Vec shade = Shading::lamb(color, l, norm);
                    frame.at<cv::Vec3b>(r, c) = cv::Vec3b(shade.x, shade.y, shade.z);
                }
            }
        }
    }
}
