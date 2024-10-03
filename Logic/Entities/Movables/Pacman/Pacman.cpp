#include "Pacman.h"
#include "../Ghost/Ghost.h"
#include "../../../../Representation/Game/SharedContext/SharedContext.h"

Pacman::Pacman() :EntityModel(){
    set_direction(EAST);
    set_size(PACMAN_SIZE,PACMAN_SIZE);
    speed = PACMAN_SPEED;
    m_pacmanStates.push(std::make_shared<PacmanState_Running>(this));
}

// take and eat functions are responsible for calling the collectable object to collect and notify the observers

void Pacman::take(const std::shared_ptr<class Coin>& collectable)
{
    if (!collectable)
        return;
    collectable->collect();
    collectable->notify("coin taken");
}

void Pacman::take(const std::shared_ptr<class Energizer>& collectable)
{
    if (!collectable)
        return;
    collectable->collect();
    collectable->notify("energizer taken");
}

void Pacman::eat(const std::shared_ptr<class Fruit>& collectable)
{
    if (!collectable)
        return;
    collectable->collect();
    collectable->notify("fruit eaten");
}
// kill function is responsible for killing the ghost and notifying the observers
void Pacman::kill(const std::shared_ptr<class Ghost>& ghost)
{
    if (!ghost)
        return;
    ghost->die();
    notify("ghost killed");
}

// die function is responsible for decreasing pacman lives and resetting its position
void Pacman::die()
{
    SharedContext::getInstance().getScore()->decrease_pacman_lives();
    set_position(get_init_position());
}
// slip function is responsible for changing pacman state to slipping
void Pacman::slip(){
    switchToState(std::make_shared<PacmanState_Slipping>(this));
}

void Pacman::move(Direction dir) {
    if (m_pacmanStates.top()) {
        m_pacmanStates.top()->move(dir);
    }
}

void Pacman::stop(){
    m_position.x = round(m_position.x);
    m_position.y = round(m_position.y);
    set_direction(NONE);
}

void Pacman::pushState(std::shared_ptr<PacmanState> pacmanState) {
    if(!m_pacmanStates.empty()){
        m_pacmanStates.top()->exit();
    }
    m_pacmanStates.push(std::move(pacmanState));
    m_pacmanStates.top()->enter();
}

void Pacman::popState() {
    if (!m_pacmanStates.empty()) {
        m_pacmanStates.top()->exit();
        m_pacmanStates.pop();
    }
    if (!m_pacmanStates.empty()) {
        m_pacmanStates.top()->enter();
    }
}

void Pacman::switchToState(const std::shared_ptr<PacmanState>& pacmanState) {
    while (!m_pacmanStates.empty()) {
        m_pacmanStates.top()->exit();
        m_pacmanStates.pop();
    }
    m_pacmanStates.push(pacmanState);
    m_pacmanStates.top()->enter();
}

bool Pacman::isSlipping() {
    if(!m_pacmanStates.empty())
        return m_pacmanStates.top()->getPacmanStateType()==PacmanStateType::Slipping;
    return false;
}

bool Pacman::isRunning() {
    if(!m_pacmanStates.empty())
        return m_pacmanStates.top()->getPacmanStateType()==PacmanStateType::Running;
    return false;
}

void Pacman::update(){
    if (!m_pacmanStates.empty()) {
        m_pacmanStates.top()->update();
    }
}
