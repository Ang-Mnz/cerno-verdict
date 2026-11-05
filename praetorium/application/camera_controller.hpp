
#pragma once

#include <sys/types.h>
#include <string>

class CameraController
{
public:
	CameraController(
        const std::string& python_path,
        const std::string& script_path
    );
    ~CameraController();

    bool start();
    bool set_privacy_mode(bool enabled);
    void stop();

private:
    bool send_command(const char* command);
    bool receive_response(const char* expected_response);

    pid_t process_id_ = -1;

    int input_pipe_[2] = {-1, -1};
    int output_pipe_[2] = {-1, -1};

	std::string python_path_;
	std::string script_path_;
};
