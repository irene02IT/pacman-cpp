#include "SharedContext.h"

#include <utility>

SharedContext::SharedContext() :m_gameMap(nullptr),m_world(nullptr),score(nullptr){
    std::cout<<"shared context created"<<std::endl;
}

SharedContext::~SharedContext() {
    std::cout<<"destroying shared context"<<std::endl;
    init();
}

const std::shared_ptr<Map> &SharedContext::getGameMap() const  {
    return m_gameMap;
}

const std::shared_ptr<World> &SharedContext::getWorld() const {
    return m_world;
}

const std::shared_ptr<Score> &SharedContext::getScore() const {
    return score;
}

void SharedContext::setGameMap(std::shared_ptr<Map> map) {
    m_gameMap = std::move(map);
}

void SharedContext::setScore(std::shared_ptr<Score> score_) {
    SharedContext::score = std::move(score_);
}

void SharedContext::init() {
    m_gameMap = nullptr;
    m_world = nullptr;
    score = nullptr;
}

void SharedContext::setWorld(std::shared_ptr<World> world) {
    m_world = std::move(world);
}

