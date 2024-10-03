#ifndef INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_FEARING_H
#define INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_FEARING_H

#include "GhostState.h"
#include "../../../Logic/Utilities/StopWatch.h"

class GhostState_Fearing : public GhostState{
private:
    float fearingTime;
public:
    void setFearingTime(float fearingTime);

public:
    explicit GhostState_Fearing(Ghost* ghost);

    void enter() override;
    void update()override;
    void exit() override;

    GhostStateType getGhostStateType() override;
    void switchToChasing();
    void switchToSpawning();

    std::vector<Cell *> calc_path_to_target() override;

};


#endif //INC_2023_PROJECT_IRENE02IT_GHOSTSTATE_FEARING_H
