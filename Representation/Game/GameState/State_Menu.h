#ifndef INC_2023_PROJECT_IRENE02IT_STATE_MENU_H
#define INC_2023_PROJECT_IRENE02IT_STATE_MENU_H


#include "BaseState.h"
#include "../../../Logic/Utilities/Global.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// State menu is responsible for displaying the main menu of the game and creating the score object,
// since it needs to display the top scores.
class State_Menu: public BaseState{
public:
    explicit State_Menu(StateManager *stateManager);

    ~State_Menu() override;

    static void CreateScore();

    void enter()override;

    void exit()override;

    void Draw()override;

    void SetUp();

    void ProcessInput()override;

    void HandleMouseClick(int x, int y);

    static const std::string * getTopScores();

    void switchToStateLevel();

private:
    sf::Font m_font;
    sf::Text m_text;

    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding{};

    sf::RectangleShape m_rects[MAP_MAZE_PATHS.size()+1]; // buttons are one per maze +1 for the back button
    sf::Text m_labels[MAP_MAZE_PATHS.size()+1]; // same as above

    sf::Text sc_text; // label for top scores
    sf::Text sc_rank[5]; // top 5 scores values

};


#endif //INC_2023_PROJECT_IRENE02IT_STATE_MENU_H
