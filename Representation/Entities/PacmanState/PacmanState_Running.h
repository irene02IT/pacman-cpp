#ifndef INC_2023_PROJECT_IRENE02IT_PACMANSTATE_RUNNING_H
#define INC_2023_PROJECT_IRENE02IT_PACMANSTATE_RUNNING_H

#include "PacmanState.h"

class PacmanState_Running: public PacmanState{
public:
    explicit PacmanState_Running(class Pacman *pacmanStateManager) : PacmanState(pacmanStateManager){};
    PacmanStateType getPacmanStateType() override;
    void update() override;
    void enter() override;
    void exit() override;
    void move(Direction dir) override;

    void switchToSlipping();
};


#endif //INC_2023_PROJECT_IRENE02IT_PACMANSTATE_RUNNING_H
