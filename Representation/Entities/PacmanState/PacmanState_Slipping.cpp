#include "PacmanState_Slipping.h"
#include "../../../Logic/Entities/Movables/Pacman/Pacman.h"
#include "../../../Logic/Utilities/StopWatch.h"

PacmanStateType PacmanState_Slipping::getPacmanStateType() {
    return PacmanStateType::Running;
}

void PacmanState_Slipping::update() {
    m_slippingTimer += StopWatch::getInstance().getElapsedTime();
    if (m_slippingTimer/0.25 > SLIPPING_DURATION) {
        switchToRunning();
    }
}

void PacmanState_Slipping::enter() {
    StopWatch::getInstance().start();
    m_slippingTimer = 0.0f;
    std::cout << "Slipping enter" << std::endl;
}

void PacmanState_Slipping::exit() {
    std::cout << "Slipping exit" << std::endl;
}

void PacmanState_Slipping::switchToRunning() {
    pacmanStateManager->pushState(std::make_unique<PacmanState_Running>(pacmanStateManager));
}

void PacmanState_Slipping::move(Direction dir) {
    pacmanStateManager->stop();
}
