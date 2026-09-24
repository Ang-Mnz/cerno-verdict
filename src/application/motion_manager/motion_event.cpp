#include "motion_event.hpp"

namespace
{
    std::uint64_t next_event_id = 1;
}

MotionEvent::MotionEvent()
    : active_(false),
	id_(next_event_id++)
{
}

std::uint64_t MotionEvent::id() const
{
    return id_;
}

void MotionEvent::start(const cv::Mat& frame)
{
    active_ = true;

    start_time_ = std::chrono::steady_clock::now();
	timestamp_ = std::chrono::system_clock::now();

    frame.copyTo(image_);
}

void MotionEvent::end()
{
    active_ = false;

    end_time_ = std::chrono::steady_clock::now();
}

bool MotionEvent::is_active() const
{
    return active_;
}

std::chrono::steady_clock::time_point MotionEvent::start_time() const
{
    return start_time_;
}

std::chrono::steady_clock::time_point MotionEvent::end_time() const
{
    return end_time_;
}

std::chrono::system_clock::time_point MotionEvent::timestamp() const
{
    return timestamp_;
}

std::chrono::milliseconds MotionEvent::duration() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time_ - start_time_
    );
}

const cv::Mat& MotionEvent::image() const
{
    return image_;
}

bool MotionEvent::save_image(const std::string& path) const
{
    if (image_.empty())
    {
        return false;
    }

    return cv::imwrite(path, image_);
}

std::string MotionEvent::image_filename() const
{
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp_);

    std::tm local_time{};

    localtime_r(&time, &local_time);

    std::ostringstream filename;

    filename << "motion_"
             << std::put_time(&local_time, "%Y-%m-%d_%H-%M-%S")
             << ".jpg";

    return filename.str();
}
