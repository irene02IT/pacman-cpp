#ifndef INC_2023_PROJECT_IRENE02IT_STATE_VICTORY_H
#define INC_2023_PROJECT_IRENE02IT_STATE_VICTORY_H


#include "BaseState.h"
#include "../../../Logic/Utilities/Global.h"
#include "../SharedContext/SharedContext.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
class State_Victory : public BaseState{
public:
    explicit State_Victory(StateManager *stateManager);
    void enter()override;
    void exit()override;
    void ProcessInput() override;
    void SetUp();
    void Draw()override;
    void switchToStateLevel();

    ~State_Victory() override;
    static void loadNextMaze();
private:
    sf::Font m_font;
    sf::Text m_text[2];
    sf::RectangleShape m_rect;
    void HandleKeyPress(sf::Keyboard::Key key);
};


#endif //INC_2023_PROJECT_IRENE02IT_STATE_VICTORY_H
