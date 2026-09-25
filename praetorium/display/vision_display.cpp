#include "vision_display.hpp"

VisionDisplay::VisionDisplay()
    : width_(800),
      height_(600)
{
    cv::namedWindow("camera", cv::WINDOW_NORMAL);
    cv::namedWindow("Motion Mask", cv::WINDOW_NORMAL);

    cv::resizeWindow("camera", width_, height_);
    cv::resizeWindow("Motion Mask", width_, height_);
}

void VisionDisplay::show(
    const cv::Mat& frame,
    const cv::Mat& motion_mask)
{
    cv::imshow("camera", frame);
    cv::imshow("Motion Mask", motion_mask);
}

bool VisionDisplay::should_close() const
{
    int key = cv::waitKey(1);

    return key == 'q' || key == 27;
}

void VisionDisplay::close()
{
    cv::destroyAllWindows();
}
