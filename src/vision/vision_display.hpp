#pragma once

#include <opencv2/opencv.hpp>

class VisionDisplay
{
public:
    VisionDisplay();

    void show(const cv::Mat& frame, const cv::Mat& motion_mask);
    bool should_close() const;
    void close();

private:
    int width_;
    int height_;
};
