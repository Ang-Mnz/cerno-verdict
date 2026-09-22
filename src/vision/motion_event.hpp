#pragma once

#include <chrono>
#include <string>

#include <opencv2/opencv.hpp>

class MotionEvent
{
public:
    MotionEvent();

    void start(const cv::Mat& frame);
    void end();

    bool is_active() const;

	std::chrono::steady_clock::time_point start_time() const;
    std::chrono::steady_clock::time_point end_time() const;

    std::chrono::milliseconds duration() const;

	std::chrono::system_clock::time_point timestamp() const;

    const cv::Mat& image() const;
	bool save_image(const std::string& path) const;
	std::string image_filename() const;

private:
    bool active_;

	std::chrono::steady_clock::time_point start_time_;
    std::chrono::steady_clock::time_point end_time_;

	std::chrono::system_clock::time_point timestamp_;

    cv::Mat image_;
};
