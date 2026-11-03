#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Camera
{
public:
    Camera();
    ~Camera();

    bool open(const std::string& source);
    bool read(cv::Mat& frame);
	void close();

private:
    cv::VideoCapture capture_;
};
