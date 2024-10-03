#include "PacmanState_Running.h"
#include "../../../Logic/Entities/Movables/Pacman/Pacman.h"
#include "../../Game/SharedContext/SharedContext.h"

PacmanStateType PacmanState_Running::getPacmanStateType() {
    return PacmanStateType::Slipping;
}

void PacmanState_Running::update() {}

void PacmanState_Running::enter() {}

void PacmanState_Running::exit() {}

void PacmanState_Running::switchToSlipping() {
    pacmanStateManager->pushState(std::make_unique<PacmanState_Slipping>(pacmanStateManager));
}

void PacmanState_Running::move(Direction dir) {
    Position oldPos = pacmanStateManager->get_position();
        switch (dir) {
            case EAST:
                pacmanStateManager->moveRight();
                break;
            case SOUTH:
                pacmanStateManager->moveDown();
                break;
            case WEST:
                pacmanStateManager->moveLeft();
                break;
            case NORTH:
                pacmanStateManager->moveUp();
                break;
            case NONE:
                break;
        }
        //SharedContext::getInstance().getGameMap()->updateEntityPosition(CellType::Pacman, pacmanStateManager->get_position());
        SharedContext::getInstance().getGameMap()->getGrid()->moveEntityFromTo(CellType::Pacman, oldPos.x, oldPos.y,pacmanStateManager->get_position().x,pacmanStateManager->get_position().y);
}
