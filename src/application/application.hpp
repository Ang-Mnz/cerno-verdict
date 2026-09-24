#pragma once

#include <string>

#include "communication/uart.hpp"

#include "vision/camera.hpp"
#include "vision/motion_detector.hpp"
#include "vision/vision_display.hpp"

#include "application/motion_manager/motion_manager.hpp"

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
	MotionManager motion_manager_;


    void process_command(const std::string& command);
};
