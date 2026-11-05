#include "vision/camera_stream/camera_stream.hpp"

CameraStream::CameraStream()
{
}

CameraStream::~CameraStream()
{
    if (capture_.isOpened())
    {
        capture_.release();
    }
}

bool CameraStream::open(const std::string& source)
{
    return capture_.open(source);
}

bool CameraStream::read(cv::Mat& frame)
{
    return capture_.read(frame);
}

void CameraStream::close()
{
    if (capture_.isOpened())
    {
        capture_.release();
    }
}
