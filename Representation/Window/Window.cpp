#include "Window.h"
Window::Window(const std::string &title, const sf::Vector2u &size) {
    Setup(title, size);
}
Window::Window() {
    Setup(WINDOW_TITLE, sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
}

std::shared_ptr<sf::RenderWindow> Window::GetRenderWindow() {
    return m_window;
}

bool Window::IsOpen() {
    return m_window->isOpen();
}

void Window::Close() {
    m_window->close();
}

void Window::Display() {
    m_window->display();
}

void Window::Clear() {
    m_window->clear( sf::Color::Black );
}

void Window::Setup(const std::string &title, const sf::Vector2u &size)  {
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullscreen = false;
    Create();
}

void Window::Create(){
    sf::Uint32 style = sf::Style::Close;
    if (m_isFullscreen) {
        style = sf::Style::Fullscreen;
    }
    m_window = std::make_shared<sf::RenderWindow>();
    m_window->create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);
}

Window::~Window() {
    Close();
}

