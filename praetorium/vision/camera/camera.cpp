#include "vision/camera/camera.hpp"

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

bool Camera::open(const std::string& source)
{
    return capture_.open(source);
}

bool Camera::read(cv::Mat& frame)
{
    return capture_.read(frame);
}
