#include "State_Menu.h"

#include "State_Level.h"
#include "StateManager.h"
#include "../../../Logic/Utilities/Random.h"


State_Menu::State_Menu(StateManager *stateManager) : BaseState(stateManager){
    CreateScore();
    SetUp();
}

State_Menu::~State_Menu() {
    std::cout<<"destroying State_Menu"<<std::endl;
}
void State_Menu::enter() {
    std::cout<<"welcome State_Menu"<<std::endl;
}
void State_Menu::exit() {
    std::cout<<"bye bye State_Menu"<<std::endl;
}

// Set up the visual elements of the menu.
void State_Menu::SetUp(){
    sf::Vector2u windowSize = Window::getInstance().GetRenderWindow()->getSize();
    m_font.loadFromFile("../" + FONT_PATH);
    m_text.setFont(m_font);
    m_text.setString(sf::String("MAIN MENU"));
    m_text.setCharacterSize(FONT_SIZE_H1);

    sf::FloatRect textRect = m_text.getLocalBounds();

    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);

    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 9.0f);
    m_buttonSize = sf::Vector2f(600.0f, 64.0f);
    m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 4.0f);
    m_buttonPadding = 4; // 4px.

    std::string str[MAZES_COUNT+1];
    for(int i = 0; i < MAZES_COUNT+1; i++){
        str[i] = "PLAY WITH MAZE " + std::to_string(i+1);
    }
    str[MAZES_COUNT] = "EXIT";

    for (int i = 0; i < MAZES_COUNT+1; ++i) {
        sf::Vector2f buttonPosition(m_buttonPos.x,
                                    m_buttonPos.y + (i * (m_buttonSize.y + m_buttonPadding)));
        m_rects[i].setSize(m_buttonSize);
        m_rects[i].setFillColor(sf::Color::Red);

        m_rects[i].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
        m_rects[i].setPosition(buttonPosition);

        m_labels[i].setFont(m_font);
        m_labels[i].setString(sf::String(str[i]));
        m_labels[i].setCharacterSize(FONT_SIZE_H2);

        sf::FloatRect rect = m_labels[i].getLocalBounds();
        m_labels[i].setOrigin(rect.left + rect.width / 2.0f,
                              rect.top + rect.height / 2.0f);

        m_labels[i].setPosition(buttonPosition);
    }
    //display top 5 scores
    sc_text.setFont(m_font);
    sc_text.setString("Top 5 scores:");
    sc_text.setCharacterSize(FONT_SIZE_H1);

    sc_text.setPosition(windowSize.x / 4.5f, m_rects[2].getPosition().y+150);

    const std::string* topScores = getTopScores();
    for (int j = 0; j < 5; j++) {
        if (topScores[j]!="0") {
            sc_rank[j].setString(topScores[j]);
        } else {
            sc_rank[j].setString("");
        }
    }
    sf::Vector2<float> k = sc_text.getPosition();
    for (auto & i : sc_rank){
        if(i.getString()!=""){
            i.setFont(m_font);
            i.setCharacterSize(FONT_SIZE_H2);
            i.setPosition(windowSize.x / 2-50, k.y+50);
            k.y+=30;
        }
    }

}

void State_Menu::Draw() {
    std::shared_ptr<sf::RenderWindow> window = Window::getInstance().GetRenderWindow();
    window->draw(m_text);
    for (int i = 0; i < MAZES_COUNT+1; ++i) {
        window->draw(m_rects[i]);
        window->draw(m_labels[i]);
    }
    window->draw(sc_text);
    for (const auto & i : sc_rank) {
        window->draw(i);
    }
}

void State_Menu::ProcessInput() {
    sf::Event event;
    while (Window::getInstance().GetRenderWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                Window::getInstance().Close();
                break;
            case sf::Event::MouseButtonPressed:
                HandleMouseClick(event.mouseButton.x, event.mouseButton.y);
            default:
                // Handle any other events
                break;
        }
    }
}

// function to handle mouse click event.
// Since the user can decide which maze to play by clicking on the button,
// the responsibility of map creation (according to the number of maze chosen) is given to StateMenu
void State_Menu::HandleMouseClick(int x, int y) {
    sf::Vector2f mousePos(x, y);
    for(int i = 0; i < MAZES_COUNT+1; ++i) {
        sf::FloatRect buttonBounds = m_rects[i].getGlobalBounds();

        if(buttonBounds.contains(mousePos)) {
            std::cout << "Button " << i << " is clicked.\n";
            // if the user clicks on a maze button, create the map and switch to the level state.
            if(i>=0 && i<MAZES_COUNT){
                SharedContext::getInstance().setGameMap(std::make_shared<Map>(i)); //set the map according to the maze number.
                switchToStateLevel();
            }else if(i==MAZES_COUNT){ // if the user clicks on the exit button, close the window.
                Window::getInstance().Close();
            }
            break;
        }
    }
}

void State_Menu::switchToStateLevel(){
    m_stateManager->setNewState(StateType::Level, StateType::Menu);
}

void State_Menu::CreateScore() {
    if (!SharedContext::getInstance().getScore()) {
        SharedContext::getInstance().setScore(std::make_shared<Score>());
        auto score_view = std::make_shared<ScoreView>(SharedContext::getInstance().getScore());
        SharedContext::getInstance().getScore()->addObserver(score_view);
    }
}

const std::string * State_Menu::getTopScores() {
    return SharedContext::getInstance().getScore()->getTopScores();
}

