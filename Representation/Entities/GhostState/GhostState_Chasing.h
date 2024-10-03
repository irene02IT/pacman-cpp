#ifndef INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_CHASING_H
#define INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_CHASING_H


#include "GhostState.h"

class GhostState_Chasing : public GhostState{
public:
    explicit GhostState_Chasing(Ghost* ghost);

    void enter() override;
    void update()override;
    void exit() override;
    GhostStateType getGhostStateType() override;
    void switchToFearing();

    std::vector<Cell *> calc_path_to_target() override;
};


#endif //INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_CHASING_H
