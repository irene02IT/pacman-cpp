#ifndef INC_2023_PROJECT_IRENE02IT_STATEMANAGER_H
#define INC_2023_PROJECT_IRENE02IT_STATEMANAGER_H

#include <stack>
#include <utility>
#include "BaseState.h"
#include "State_Menu.h"
#include "State_Level.h"
#include "State_Paused.h"
#include "State_GameOver.h"
#include "State_Victory.h"

enum class StateType {
    None,
    Menu,
    Level,
    Paused,
    GameOver,
    Victory
};
// Class responsible for managing the states of the game.
// Deciding when to switch state is responsibility of each state, but the actual switching is done by the StateManager.
class StateManager {
private:
    std::stack<std::unique_ptr<BaseState>> m_states; // stack of states
    StateType m_newState = StateType::None;
    StateType m_currState = StateType::None;
public:
    StateManager();
    ~StateManager();
    void emptyStack();
    void initialize();
    void pushState(std::unique_ptr<BaseState>state);
    void popState();
    void update();
    void setNewState(StateType newState, StateType currentState);
    void switchState();
};


#endif //INC_2023_PROJECT_IRENE02IT_STATEMANAGER_H
