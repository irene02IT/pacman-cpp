#include "GhostState_Chasing.h"
#include "../../../Logic/Entities/Movables/Ghost/Ghost.h"
#include "../../Game/SharedContext/SharedContext.h"

GhostState_Chasing::GhostState_Chasing(Ghost *ghost) : GhostState(ghost) {
    gh_stateManager->set_strategy(std::make_shared<ChasingStrategy>(gh_stateManager->getGhostType()));
}

void GhostState_Chasing::enter() {
    std::cout<<"chasing mode: on"<<std::endl;
}

void GhostState_Chasing::exit() {
    std::cout<<"chasing mode: off"<<std::endl;
}
// the switchToChasing() method is not used in the codebase, since it's not responsibility of the GhostState_Chasing to switch to fearing state
void GhostState_Chasing::switchToFearing() {
    gh_stateManager->pushState(std::unique_ptr<GhostState_Fearing>());
}

GhostStateType GhostState_Chasing::getGhostStateType() {
    return GhostStateType::Chasing;
}

void GhostState_Chasing::update() {
    //gh_stateManager->update_path_to_target(calc_path_to_target());
    //gh_stateManager->move();
    gh_stateManager->moveRandomly();
}

std::vector<Cell *> GhostState_Chasing::calc_path_to_target() {
    Position&& target = gh_stateManager->get_target_position();
    return SharedContext::getInstance().getGameMap()->getPathFromTo(gh_stateManager->get_position(), target);
}

