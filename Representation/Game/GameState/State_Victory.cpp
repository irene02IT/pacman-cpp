#include "State_Victory.h"
#include "StateManager.h"

State_Victory::State_Victory(StateManager *stateManager): BaseState(stateManager){
    SharedContext::getInstance().getScore()->checkNewRecord();
    SetUp();
}

State_Victory::~State_Victory() {
    std::cout<<"destroying State_Victory"<<std::endl;
}

void State_Victory::Draw() {
    std::shared_ptr<sf::RenderWindow> window = Window::getInstance().GetRenderWindow();
    window->draw(m_rect);
    for (auto & i : m_text){
        window->draw(i);
    }
}

void State_Victory::SetUp() {
    m_font.loadFromFile("../" + FONT_PATH);
    for(auto & i : m_text){
        i.setFont(m_font);
        i.setCharacterSize(FONT_SIZE_H2);
        i.setStyle(sf::Text::Bold);
    }
    m_text[0].setString(sf::String("YOU WON!"));
    m_text[1].setString(sf::String("Press any key to continue..."));

    sf::Vector2u windowSize = Window::getInstance().GetRenderWindow()->getSize();
    int k = 1;
    for(int i = 0; i < 2; i++){
        sf::FloatRect textRect = m_text[i].getLocalBounds();
        m_text[i].setOrigin(textRect.left + textRect.width / 2.0f,
                            textRect.top + textRect.height / 2.0f);
        m_text[i].setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + i*FONT_SIZE_H2+k);
        k+=FONT_SIZE_H2;
    }


    m_rect.setSize(sf::Vector2f(windowSize));
    m_rect.setPosition(0, 0);
    m_rect.setFillColor(sf::Color(0, 0, 0, 150));
}

void State_Victory::enter() {
    std::cout<<"welcome State_Victory"<<std::endl;
}

void State_Victory::exit() {
    std::cout<<"bye bye State_Victory"<<std::endl;
}

void State_Victory::ProcessInput() {
    sf::Event event{};
    while (Window::getInstance().GetRenderWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                Window::getInstance().Close();
                break;
            case sf::Event::KeyPressed:
                HandleKeyPress(event.key.code);
                break;
            default:
                break;
        }
    }
}

void State_Victory::HandleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Escape:
            Window::getInstance().Close();
            break;
        default:
            switchToStateLevel();
            break;
    }
}
void State_Victory::switchToStateLevel(){
    loadNextMaze();
    SharedContext::getInstance().getScore()->increaseLevel();
    m_stateManager->setNewState(StateType::Level, StateType::Victory);
}

void State_Victory::loadNextMaze() {
    //select the next maze from the list
    int current_maze = SharedContext::getInstance().getGameMap()->getMazeNumber();
    if(current_maze+1 < MAZES_COUNT){
        SharedContext::getInstance().getGameMap()->setNewMaze(current_maze+1);
    }else{
        //if we are at the last maze, go back to the first one
        SharedContext::getInstance().getGameMap()->setNewMaze(0);
    }
}
