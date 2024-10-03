#ifndef INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_H
#define INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_H

#include <iostream>
#include <stack>
#include <memory>
#include "../../../Logic/Map/Map.h"

enum class GhostStateType{
    Spawning,
    Chasing,
    Fearing,
    Dead
};
class Ghost;
class GhostState {
public:
    explicit GhostState(Ghost *ghostStateManager) :gh_stateManager(ghostStateManager){};
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void exit () = 0;
    virtual GhostStateType getGhostStateType() = 0;
    virtual std::vector<Cell*> calc_path_to_target() = 0;
protected:
    Ghost* gh_stateManager;
};


#endif //INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_H
