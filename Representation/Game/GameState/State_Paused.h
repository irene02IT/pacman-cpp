#ifndef INC_2023_PROJECT_IRENE02IT_STATE_PAUSED_H
#define INC_2023_PROJECT_IRENE02IT_STATE_PAUSED_H


#include "BaseState.h"
#include "../../../Logic/Utilities/Global.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class State_Paused : public BaseState{
public:
    explicit State_Paused(StateManager *stateManager);
    void enter()override;
    void exit()override;
    void ProcessInput() override;
    void SetUp();
    void Draw()override;
    void switchToStateLevel();
    void switchToStateMenu();
    void HandleKeyPress(sf::Keyboard::Key key);
    ~State_Paused() override;
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rect;

    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding{};

    sf::RectangleShape m_rects[3];
    sf::Text m_labels[3];

    void HandleMouseClick(int x, int y);
};


#endif //INC_2023_PROJECT_IRENE02IT_STATE_PAUSED_H
