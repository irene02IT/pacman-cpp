#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager *stateManager) : BaseState(stateManager) {
    SetUp();
}

void State_Paused::enter(){
    std::cout<<"welcome State_Paused"<<std::endl;
}
void State_Paused::exit() {
    std::cout<<"bye bye State_Paused"<<std::endl;
}
State_Paused::~State_Paused() {
    std::cout<<"destroying State_Paused"<<std::endl;
}
// Set up the visual elements of the menu.
void State_Paused::SetUp(){
    sf::Vector2u windowSize = Window::getInstance().GetRenderWindow()->getSize();
    m_font.loadFromFile("../" + FONT_PATH);
    m_text.setFont(m_font);
    m_text.setString(sf::String("PAUSED"));
    m_text.setCharacterSize(FONT_SIZE_H1);

    sf::FloatRect textRect = m_text.getLocalBounds();

    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);

    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 4.0f);
    m_buttonSize = sf::Vector2f(600.0f, 64.0f);
    m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);
    m_buttonPadding = 4; // 4px.

    std::string str[2];
    str[0] = "CONTINUE";
    str[1] = "MENU";

    for (int i = 0; i < 2; ++i) {
        sf::Vector2f buttonPosition(m_buttonPos.x,
                                    m_buttonPos.y + (i * (m_buttonSize.y + m_buttonPadding)));
        m_rects[i].setSize(m_buttonSize);
        m_rects[i].setFillColor(sf::Color::Blue);

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
}
void State_Paused::Draw(){
    std::shared_ptr<sf::RenderWindow> window = Window::getInstance().GetRenderWindow();
    window->draw(m_text);
    for (int i = 0; i < 3; ++i) {
        window->draw(m_rects[i]);
        window->draw(m_labels[i]);
    }
}
void State_Paused::ProcessInput() {
    sf::Event event;
    while (Window::getInstance().GetRenderWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                Window::getInstance().Close();
                break;
            case sf::Event::KeyPressed:
                HandleKeyPress(event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                HandleMouseClick(event.mouseButton.x, event.mouseButton.y);
            default:
                break;
        }
    }
}

void State_Paused::HandleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::P:
            switchToStateLevel();
            break;
        case sf::Keyboard::Escape:
            switchToStateMenu();
            break;
        default:
            break;
    }
}
void State_Paused::HandleMouseClick(int x, int y) {

    sf::Vector2f mousePos(x, y);
    for(int i = 0; i < 3; ++i) {
        sf::FloatRect buttonBounds = m_rects[i].getGlobalBounds();

        if(buttonBounds.contains(mousePos)) {
            std::cout << "Button " << i << " is clicked.\n";
            switch (i) {
                case 0:
                    switchToStateLevel();
                    break;
                case 1:
                    switchToStateMenu();
                    break;
                default:
                    break;
            }
            break;
        }
    }
}
void State_Paused::switchToStateLevel(){
    m_stateManager->setNewState(StateType::Level, StateType::Paused);
}
void State_Paused::switchToStateMenu(){
    m_stateManager->setNewState(StateType::Menu, StateType::Paused);
}
