#pragma once

#include <string>

#include "vision/motion_event.hpp"

class EventStorage
{
public:
    EventStorage();

    bool save(const MotionEvent& event);

private:
    std::string base_path_;
};
