#include "StateManager.h"

StateManager::StateManager() {
    std::cout<<"StateManager created"<<std::endl;
}

StateManager::~StateManager() {
    std::cout<<"StateManager destroyed"<<std::endl;
}

void StateManager::emptyStack() {
    while (!m_states.empty()) {
        m_states.pop();
    }
}

void StateManager::initialize() {
    emptyStack();
    pushState(std::make_unique<State_Menu>(this));
}

void StateManager::pushState(std::unique_ptr<BaseState> state) {
    if(!m_states.empty()){
        m_states.top()->exit();
    }
    m_states.push(std::move(state));
    m_states.top()->enter();
}

void StateManager::popState() {
    if(!m_states.empty()){
        m_states.top()->exit();
        m_states.pop();
        m_states.top()->enter();
    }
}

void StateManager::update()  {
    if(m_newState != StateType::None) {
        switchState();
    }

    if(!m_states.empty()){
        m_states.top()->update();
    }
}
// set the new state and the current state to be used in switchState()
void StateManager::setNewState(StateType newState, StateType currentState)  {
    m_newState = newState;
    m_currState = currentState;
}
// switch between states is done here, based on class parameters m_newState and m_currState.
void StateManager::switchState() {
    switch (m_newState){
        case StateType::Level:
            if(m_currState == StateType::Menu)
                pushState(std::make_unique<State_Level>(this));
            else if(m_currState == StateType::Paused)
                popState();
            else if(m_currState == StateType::Victory){
                popState();
                popState();
                pushState(std::make_unique<State_Level>(this));
            }
            break;
        case StateType::Menu:
            emptyStack();
            pushState(std::make_unique<State_Menu>(this));
            break;
        case StateType::Paused:
            pushState(std::make_unique<State_Paused>(this));
            break;
        case StateType::GameOver:
            pushState(std::make_unique<State_GameOver>(this));
            break;
        case StateType::Victory:
            pushState(std::make_unique<State_Victory>(this));
            break;
        default:
            break;
    }
    // reset state
    m_newState = StateType::None;
    m_currState = StateType::None;
}
