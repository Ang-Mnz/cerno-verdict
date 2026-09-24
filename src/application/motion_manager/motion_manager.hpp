#pragma once

#include <chrono>
#include <optional>

#include <opencv2/opencv.hpp>

#include "application/motion_manager/motion_event.hpp"
#include "application/motion_manager/motion_manager_config.hpp"
#include "application/storage/events_storage.hpp"

enum class MotionState
{
    NONE,
    STARTED,
    ENDED
};

class MotionManager
{
public:
    MotionManager();

    MotionState process(const cv::Mat& frame, bool motion_detected);

private:
    std::optional<MotionEvent> motion_event_;
    EventStorage storage_;

	MotionManagerConfig config_;

    std::chrono::steady_clock::time_point last_motion_time_;

    void start_event(const cv::Mat& frame);
    void end_event();
};
