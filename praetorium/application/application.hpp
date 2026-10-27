#pragma once

#include <string>

#include "communication/communication.hpp"

#include "vision/camera/camera.hpp"
#include "vision/motion_detector.hpp"
#include "display/vision_display.hpp"

#include "application/motion_manager/motion_manager.hpp"
#include "application/application_config.hpp"

class Application
{
public:
    Application(bool headless = false);

    void run();

private:
	ApplicationConfig config_;

    Communication communication_;
	Camera camera_;
	MotionDetector motion_detector_;
	VisionDisplay display_;
	MotionManager motion_manager_;

    void process_command(const std::string& command);
};
