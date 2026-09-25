#pragma once

#include <opencv2/opencv.hpp>

#include "vision_config.hpp"

class MotionDetector
{
public:
    MotionDetector();

    bool detect(const cv::Mat& frame, cv::Mat& motion_mask);

private:
    cv::Mat previous_frame_;
	VisionConfig config_;
};
