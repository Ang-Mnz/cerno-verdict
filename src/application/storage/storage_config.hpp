#pragma once

#include <cstddef>
#include <string>

struct StorageConfig
{
    std::string path_events = "../events/";
    std::size_t max_images = 100;
};
