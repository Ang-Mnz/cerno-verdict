#pragma once

#include <opencv2/opencv.hpp>

class MotionDetector
{
public:
    MotionDetector();

    bool detect(const cv::Mat& frame);

private:
    cv::Mat previous_frame_;
};
