#ifndef INC_2023_PROJECT_IRENE02IT_STATE_GAMEOVER_H
#define INC_2023_PROJECT_IRENE02IT_STATE_GAMEOVER_H


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "../../../Logic/Utilities/Global.h"

class State_GameOver : public BaseState{
public:
    explicit State_GameOver(StateManager *stateManager);
    void enter()override;
    void exit()override;
    void ProcessInput() override;
    void SetUp();
    void Draw() override;
    void switchToMenu();

    ~State_GameOver() override;

private:
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rect;
    void HandleKeyPress(sf::Keyboard::Key key);


};


#endif //INC_2023_PROJECT_IRENE02IT_STATE_GAMEOVER_H
