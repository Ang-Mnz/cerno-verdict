#pragma once

#include <opencv2/opencv.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    bool open();
    bool read(cv::Mat& frame);

private:
    cv::VideoCapture capture_;
};
