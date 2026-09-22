#include "camera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
    if (capture_.isOpened())
    {
        capture_.release();
    }
}

bool Camera::open()
{
    return capture_.open(0);
}

bool Camera::read(cv::Mat& frame)
{
    return capture_.read(frame);
}
