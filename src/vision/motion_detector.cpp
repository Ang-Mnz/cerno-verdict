#include "motion_detector.hpp"

MotionDetector::MotionDetector()
{
}

bool MotionDetector::detect(const cv::Mat& frame)
{
    cv::Mat gray_frame;
    cv::Mat blurred_frame;

	// Passage en noir et blanc
    cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

	// Application de flou pour atténuer les petites variations
    cv::GaussianBlur(
        gray_frame,
        blurred_frame,
        cv::Size(21, 21),
        0
    );

    if (previous_frame_.empty())
    {
        blurred_frame.copyTo(previous_frame_);
        return false;
    }

    cv::Mat difference;

	// Comparaison des deux frames
    cv::absdiff(previous_frame_, blurred_frame, difference);

	// On transforme les valeurs au dessus du seuil en 255 on met le reste à zero
    cv::threshold(
        difference,
        difference,
        25,
        255,
        cv::THRESH_BINARY
    );

    previous_frame_ = blurred_frame.clone();

    return cv::countNonZero(difference) > 1000;
}
