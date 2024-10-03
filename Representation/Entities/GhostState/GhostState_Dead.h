#ifndef INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_DEAD_H
#define INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_DEAD_H


#include "GhostState.h"

class GhostState_Dead : public GhostState{
public:
    explicit GhostState_Dead(Ghost* ghost);
    void enter() override;
    void update() override;
    void exit() override;

    GhostStateType getGhostStateType() override;
    std::vector<Cell *> calc_path_to_target() override;

};


#endif //INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_DEAD_H
