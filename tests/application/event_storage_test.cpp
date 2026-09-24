#include <cassert>
#include <filesystem>

#include <opencv2/opencv.hpp>

#include "application/motion_manager/motion_event.hpp"
#include "application/storage/events_storage.hpp"

int main()
{
    EventStorage storage;

    cv::Mat frame =
        cv::Mat::zeros(480, 640, CV_8UC3);

    MotionEvent event;

    event.start(frame);
    event.end();

    bool saved =
        storage.save(event);

    assert(saved);

    std::filesystem::path events_directory =
        "../events/";

    assert(std::filesystem::exists(events_directory));

    bool image_found = false;

    for (const auto& entry :
         std::filesystem::recursive_directory_iterator(events_directory))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".jpg")
        {
            image_found = true;
            break;
        }
    }

    assert(image_found);

    return 0;
}
