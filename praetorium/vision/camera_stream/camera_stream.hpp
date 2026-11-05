#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class CameraStream
{
public:
    CameraStream();
    ~CameraStream();

    bool open(const std::string& source);
    bool read(cv::Mat& frame);
	void close();

private:
    cv::VideoCapture capture_;
};
