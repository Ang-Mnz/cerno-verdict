#include "motion_detector.hpp"


MotionDetector::MotionDetector()
{
}

bool MotionDetector::detect(const cv::Mat& frame, cv::Mat& motion_mask)
{
    cv::Mat gray_frame;
    cv::Mat blurred_frame;

	// Passage en noir et blanc
    cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

	// Application de flou pour atténuer les petites variations
    cv::GaussianBlur(
        gray_frame,
        blurred_frame,
        cv::Size(
			config_.blur_kernel_size,
			config_.blur_kernel_size
		),
        0
    );

    if (previous_frame_.empty())
    {
        blurred_frame.copyTo(previous_frame_);
		motion_mask = cv::Mat::zeros(blurred_frame.size(), CV_8UC1);
        return false;
    }

    cv::Mat difference;

	// Comparaison des deux frames
    cv::absdiff(previous_frame_, blurred_frame, difference);

	// On transforme les valeurs au dessus du seuil en 255 on met le reste à zero
    cv::threshold(
        difference,
        motion_mask,
        config_.threshold_value,
        255,
        cv::THRESH_BINARY
    );

    previous_frame_ = blurred_frame.clone();

    int motion_pixels = cv::countNonZero(motion_mask);

	return motion_pixels > config_.motion_pixel_threshold;
}
