#ifndef INC_2023_PROJECT_IRENE02IT_PACMANSTATE_SLIPPING_H
#define INC_2023_PROJECT_IRENE02IT_PACMANSTATE_SLIPPING_H


#include "PacmanState.h"

class PacmanState_Slipping : public PacmanState{
private:
    float m_slippingTimer = 0.0f;
public:
    explicit PacmanState_Slipping(class Pacman *pacmanStateManager) : PacmanState(pacmanStateManager){};
    PacmanStateType getPacmanStateType() override;
    void update() override;
    void enter() override;
    void exit() override;
    void move(Direction dir) override;
    void switchToRunning();
};


#endif //INC_2023_PROJECT_IRENE02IT_PACMANSTATE_SLIPPING_H
