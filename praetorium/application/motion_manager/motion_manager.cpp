#include "application/motion_manager/motion_manager.hpp"


MotionManager::MotionManager()
{
}

void MotionManager::start_event(const cv::Mat& frame)
{
    motion_event_.emplace();
    motion_event_->start(frame);
}

void MotionManager::end_event()
{
    motion_event_->end();
    storage_.save(*motion_event_);

    motion_event_.reset();
}

void MotionManager::stop()
{
    if (motion_event_)
    {
        end_event();
    }
}

MotionState MotionManager::process(
    const cv::Mat& frame,
    bool motion_detected)
{
    if (motion_detected)
    {
        last_motion_time_ = std::chrono::steady_clock::now();

        if (!motion_event_)
        {
            start_event(frame);
            return MotionState::STARTED;
        }

        return MotionState::NONE;
    }

    if (!motion_event_)
    {
        return MotionState::NONE;
    }

    auto now = std::chrono::steady_clock::now();

    if (now - last_motion_time_ >= config_.motion_end_delay)
    {
        end_event();
        return MotionState::ENDED;
    }

    return MotionState::NONE;
}
