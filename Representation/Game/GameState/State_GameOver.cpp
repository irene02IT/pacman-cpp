#include "State_GameOver.h"
#include "StateManager.h"

State_GameOver::State_GameOver(StateManager *stateManager) : BaseState(stateManager) {
    SharedContext::getInstance().getScore()->checkNewRecord();
    SharedContext::getInstance().init(); // Reset shared context for new game
    SetUp();
}

State_GameOver::~State_GameOver() {
    std::cout<<"destroying State_GameOver"<<std::endl;
}

void State_GameOver::enter() {
    std::cout<<"welcome State_GameOver"<<std::endl;
}

void State_GameOver::exit() {
    std::cout<<"bye bye State_GameOver"<<std::endl;
}

void State_GameOver::SetUp() {
    m_font.loadFromFile("../" + FONT_PATH);
    m_text.setFont(m_font);
    m_text.setString(sf::String("GAME OVER"));
    m_text.setCharacterSize(FONT_SIZE_H1);
    m_text.setStyle(sf::Text::Bold);

    sf::Vector2u windowSize = Window::getInstance().GetRenderWindow()->getSize();

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    m_rect.setSize(sf::Vector2f(windowSize));
    m_rect.setPosition(0, 0);
    m_rect.setFillColor(sf::Color(0, 0, 0, 150));
}

void State_GameOver::Draw() {
    std::shared_ptr<sf::RenderWindow> window =Window::getInstance().GetRenderWindow();
    window->draw(m_rect);
    window->draw(m_text);
}
void State_GameOver::ProcessInput() {
    sf::Event event{};
    while (Window::getInstance().GetRenderWindow()->pollEvent(event)) {
        if(event.type ==sf::Event::Closed)
            Window::getInstance().Close();
        if(event.type == sf::Event::KeyPressed)
            HandleKeyPress(event.key.code);
    }
}
void State_GameOver::HandleKeyPress(sf::Keyboard::Key key) {
    if(key ==sf::Keyboard::Escape)
        Window::getInstance().Close();
    if(key == sf::Keyboard::Enter)
        switchToMenu();
}
void State_GameOver::switchToMenu(){
    m_stateManager->setNewState(StateType::Menu, StateType::GameOver);
}