#include "GhostState_Dead.h"
#include "../../../Logic/Entities/Movables/Ghost/Ghost.h"
#include "../../Game/SharedContext/SharedContext.h"

GhostState_Dead::GhostState_Dead(Ghost *ghost) : GhostState(ghost) {
    gh_stateManager->set_strategy(std::make_shared<DeadStrategy>(gh_stateManager->getGhostType()));
}

void GhostState_Dead::enter() {
    std::cout<<"dead mode: on"<<std::endl;
    gh_stateManager->setSpawned(false);
}

void GhostState_Dead::exit() {
    std::cout<<"dead mode: off"<<std::endl;
}

GhostStateType GhostState_Dead::getGhostStateType() {
    return GhostStateType::Dead;
}

void GhostState_Dead::update() {
    if(gh_stateManager->get_init_position()!=gh_stateManager->get_position()){
        //gh_stateManager->back_to_init_position();
        gh_stateManager->update_path_to_target(calc_path_to_target());
        gh_stateManager->move();
    }else
        gh_stateManager->switchToState(GhostStateType::Spawning);
}

std::vector<Cell *> GhostState_Dead::calc_path_to_target() {
    Position&& target = gh_stateManager->get_target_position();
    return SharedContext::getInstance().getGameMap()->getPathFromTo(gh_stateManager->get_position(), target);
}