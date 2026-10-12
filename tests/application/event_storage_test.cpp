#include <cassert>
#include <filesystem>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "application/motion_manager/motion_event.hpp"
#include "application/storage/events_storage.hpp"

int main()
{
	StorageConfig config;
	config.path_events =
	(std::filesystem::temp_directory_path() / "cerno_verdict_test_events").string();

	std::filesystem::remove_all(config.path_events);

	EventStorage storage(config);

	cv::Mat frame =
		cv::Mat::zeros(480, 640, CV_8UC3);

	MotionEvent event;

	event.start(frame);
	event.end();

	bool saved =
		storage.save(event);

	assert(saved);

	bool image_found = false;

	for (const auto& entry :
		std::filesystem::recursive_directory_iterator(config.path_events))
	{
		if (entry.is_regular_file() &&
			entry.path().extension() == ".jpg")
		{
			image_found = true;
			break;
		}
	}

	assert(image_found);

	std::filesystem::remove_all(config.path_events);

	std::cout << "EventStorage tests passed." << std::endl;

	return 0;

}
