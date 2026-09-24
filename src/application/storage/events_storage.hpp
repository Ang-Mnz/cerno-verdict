#pragma once

#include <string>

#include "application/motion_manager/motion_event.hpp"
#include "application/storage/storage_config.hpp"

class EventStorage
{
public:
    EventStorage();

    bool save(const MotionEvent& event);

private:
    StorageConfig config_;

    void enforce_limit();
};
