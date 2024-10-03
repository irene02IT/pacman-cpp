#include "GhostState_Spawning.h"
#include "../../../Logic/Entities/Movables/Ghost/Ghost.h"
#include "../../Game/SharedContext/SharedContext.h"

GhostState_Spawning::GhostState_Spawning(Ghost *ghost) : GhostState(ghost) {
    gh_stateManager->set_strategy(std::make_shared<SpawningStrategy>(gh_stateManager->getGhostType()));
    gh_stateManager->setSpawned(false);
    //back to initial position
    gh_stateManager->set_position(gh_stateManager->getInitPosition());
}
void GhostState_Spawning::enter() {
    std::cout<<"spawning mode: on"<<std::endl;
}

void GhostState_Spawning::exit() {
    std::cout<<"spawning mode: off"<<std::endl;
}

GhostStateType GhostState_Spawning::getGhostStateType() {
    return GhostStateType::Spawning;
}

void GhostState_Spawning::update() {
    Position spawnPoint = gh_stateManager->getSpawnPoint();
    if(spawnPoint.y>=(gh_stateManager->get_position().y)){
        gh_stateManager->setSpawned(true);
        switchToChasing();
    }else{
        gh_stateManager->update_path_to_target(calc_path_to_target());
        gh_stateManager->move();
    }
}

void GhostState_Spawning::switchToChasing() {
    gh_stateManager->switchToState(GhostStateType::Chasing);
}

std::vector<Cell *> GhostState_Spawning::calc_path_to_target() {
    Position&& target = gh_stateManager->get_target_position();
    return SharedContext::getInstance().getGameMap()->getPathFromTo(gh_stateManager->get_position(), target);
}
