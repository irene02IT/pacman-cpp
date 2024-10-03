#ifndef INC_2023_PROJECT_IRENE02IT_PACMANSTATE_H
#define INC_2023_PROJECT_IRENE02IT_PACMANSTATE_H

#include <iostream>
#include <memory>
#include "../../../Logic/Utilities/Global.h"

class Pacman;

enum class PacmanStateType{
    Running,
    Slipping
};
class PacmanState {
public:
    explicit PacmanState(class Pacman *pacmanStateManager) :pacmanStateManager(pacmanStateManager){};
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void move(Direction dir) = 0;
    virtual void exit () = 0;
    virtual PacmanStateType getPacmanStateType() = 0;
protected:
    class Pacman *pacmanStateManager;
};


#endif //INC_2023_PROJECT_IRENE02IT_PACMANSTATE_H
