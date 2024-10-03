#ifndef INC_2023_PROJECT_IRENE02IT_STATE_LEVEL_H
#define INC_2023_PROJECT_IRENE02IT_STATE_LEVEL_H

#include "BaseState.h"
#include "../../Entities/ConcreteFactory/EntityFactory.h"
#include <memory>
#include <utility>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class State_Level : public BaseState{
public:
    explicit State_Level(StateManager *stateManager);
    void update() override;
    void enter()override;
    void exit()override{
        std::cout<<"bye bye State_Level"<<std::endl;
    }
    void Draw() override{}
    void SetUp();
    void ProcessInput() override;

    void HandleKeyPress(sf::Keyboard::Key key);
    void CreateWorld();
    void checkVictoryOrGameOver();

    ~State_Level() override;

private:
    std::shared_ptr<World> m_world;
    float m_gameTime{};
};


#endif //INC_2023_PROJECT_IRENE02IT_STATE_LEVEL_H
