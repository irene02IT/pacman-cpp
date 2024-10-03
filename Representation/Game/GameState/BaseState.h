#ifndef INC_2023_PROJECT_IRENE02IT_BASESTATE_H
#define INC_2023_PROJECT_IRENE02IT_BASESTATE_H

#include <memory>
#include <utility>
#include <iostream>

// Base class for all states.
class StateManager;
class BaseState {
public:
    explicit BaseState(StateManager* stateManager): m_stateManager(stateManager){};

    virtual ~BaseState() = default;

    virtual void update() {
        Draw();
        ProcessInput();
    }

    virtual void Draw() = 0;

    virtual void ProcessInput() = 0;

    virtual void enter() = 0;

    virtual void exit () = 0;

protected:
    StateManager* m_stateManager;
};


#endif //INC_2023_PROJECT_IRENE02IT_BASESTATE_H
