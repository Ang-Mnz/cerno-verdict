#pragma once

#include <string>

#include "communication/uart.hpp"
#include "vision/camera.hpp"
#include "vision/motion_detector.hpp"
#include "vision/vision_display.hpp"

class Application
{
public:
    Application();

    void run();

private:
    Uart uart_;
	Camera camera_;
	MotionDetector motion_detector_;
	VisionDisplay display_;

	bool motion_active_;

    void process_command(const std::string& command);
};
