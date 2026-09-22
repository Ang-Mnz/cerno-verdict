#include <filesystem>

#include "events_storage.hpp"

EventStorage::EventStorage()
    : base_path_("../events/")
{
}

bool EventStorage::save(const MotionEvent& event)
{
    std::time_t time =
        std::chrono::system_clock::to_time_t(event.timestamp());

    std::tm local_time{};

    localtime_r(&time, &local_time);

    std::ostringstream date;

    date << std::put_time(&local_time, "%Y-%m-%d");

    std::filesystem::path directory =
        std::filesystem::path(base_path_) / date.str();

    std::filesystem::create_directories(directory);

    std::filesystem::path path =
        directory / event.image_filename();

    return event.save_image(path.string());
}
