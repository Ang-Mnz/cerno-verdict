#pragma once

#include <chrono>

struct MotionManagerConfig
{
    std::chrono::milliseconds motion_end_delay{1000};
};
