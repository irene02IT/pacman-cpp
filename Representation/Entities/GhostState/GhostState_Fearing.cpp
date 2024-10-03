#include "GhostState_Fearing.h"
#include "../../../Logic/Entities/Movables/Ghost/Ghost.h"
#include "../../Game/SharedContext/SharedContext.h"

GhostState_Fearing::GhostState_Fearing(Ghost *ghost) : GhostState(ghost) {
    gh_stateManager->set_strategy(std::make_shared<FearingStrategy>(gh_stateManager->getGhostType()));
    int level = SharedContext::getInstance().getScore()->getLevelReached();
    // decrease fearing time by 1 second for each level
    if(level>1)
        fearingTime = 10 - (level-1);
    else
        fearingTime = 10;
}

void GhostState_Fearing::enter() {
    std::cout<<"entering in fearing mode"<<std::endl;
    gh_stateManager->set_speed(GHOST_FEARING_SPEED);
    fearingTime = StopWatch::getInstance().getElapsedTime();
}

void GhostState_Fearing::exit() {
    std::cout<<"exiting from fearing mode"<<std::endl;
    gh_stateManager->set_init_speed();
}

void GhostState_Fearing::switchToChasing() {
    gh_stateManager->switchToState(GhostStateType::Spawning);
}

void GhostState_Fearing::switchToSpawning() {
    gh_stateManager->initialize();
}

GhostStateType GhostState_Fearing::getGhostStateType() {
    return GhostStateType::Fearing;
}

void GhostState_Fearing::update() {
    float deltaTime = StopWatch::getInstance().getElapsedTime();
    if (fearingTime < 1) {
        // Add deltaTime to fearingTime
        fearingTime += deltaTime;
        //gh_stateManager->move();
        gh_stateManager->moveRandomly();
    } else {
        // back to spawning
        gh_stateManager->popState();
    }
}

std::vector<Cell *> GhostState_Fearing::calc_path_to_target() {
    Position&& target = gh_stateManager->get_target_position();
    return SharedContext::getInstance().getGameMap()->getPathFromTo(gh_stateManager->get_position(), target);
}
