#include <cassert>
#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>

#include "application/motion_manager/motion_manager.hpp"
#include "application/motion_manager/motion_manager_config.hpp"

int main()
{
    MotionManager manager;
	MotionManagerConfig config;

    cv::Mat frame =
        cv::Mat::zeros(480, 640, CV_8UC3);

    // Début d'un mouvement
    MotionState state =
        manager.process(frame, true);

    assert(state == MotionState::STARTED);

    // Le mouvement continue
    state =
        manager.process(frame, true);

    assert(state == MotionState::NONE);

    // Pas encore assez de temps écoulé
    state =
        manager.process(frame, false);

    assert(state == MotionState::NONE);

    // Attente de la fin de l'événement
    std::this_thread::sleep_for(
        config.motion_end_delay + std::chrono::milliseconds(100)
    );

    state =
        manager.process(frame, false);

    assert(state == MotionState::ENDED);

	////////////////////////////////////////////////////////////////////
	// Nouveau mouvement
	////////////////////////////////////////////////////////////////////

    state =
        manager.process(frame, true);

    assert(state == MotionState::STARTED);

    // Le mouvement continue
    for (int i = 0; i < 10; i++)
    {
        state =
            manager.process(frame, true);

        assert(state == MotionState::NONE);
    }

    // Fin du mouvement
    std::this_thread::sleep_for(
        config.motion_end_delay + std::chrono::milliseconds(100)
    );

    state =
        manager.process(frame, false);

    assert(state == MotionState::ENDED);

	////////////////////////////////////////////////////////////////////
	// Nouveau mouvement après la fin du précédent
	////////////////////////////////////////////////////////////////////

	state =
        manager.process(frame, true);

    assert(state == MotionState::STARTED);

    // Le mouvement continue
    state =
        manager.process(frame, true);

    assert(state == MotionState::NONE);

    // Fin du deuxième mouvement
    std::this_thread::sleep_for(
        config.motion_end_delay + std::chrono::milliseconds(100)
    );

    state =
        manager.process(frame, false);

    assert(state == MotionState::ENDED);

    return 0;
}
