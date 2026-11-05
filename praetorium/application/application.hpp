#pragma once

#include <string>

#include "communication_vigile/communication.hpp"

#include "vision/camera_stream/camera_stream.hpp"
#include "vision/motion_detector.hpp"
#include "display/vision_display.hpp"

#include "application/motion_manager/motion_manager.hpp"
#include "application/camera_controller.hpp"
#include "application/application_config.hpp"

class Application
{
public:
    Application(bool headless = false);

    void run();

private:

	bool active_ = false;

	ApplicationConfig config_;

	CameraController camera_controller_;

    Communication communication_;
	CameraStream camera_stream_;
	MotionDetector motion_detector_;
	VisionDisplay display_;
	MotionManager motion_manager_;

	std::string receive_buffer_;
    void process_send_command(const std::string& command);
	void process_received_command(const std::string& command);
};
