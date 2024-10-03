#include "Game.h"

Game::~Game() {
    std::cout<<"game destroyed"<<std::endl;
}

Game::Game() {
    std::cout<<"game created"<<std::endl;
    Setup(); // Set up the game when it is created
}

// Initialization of the shared context, window and state manager
void Game::Setup() {
    SharedContext::getInstance();
    Window::getInstance();
    m_stateManager = std::make_shared<StateManager>();
    m_stateManager->initialize();
}
// Display the window and render the game
void Game::Render() {
    Window::getInstance().Display();
}
// Close the game
void Game::Close() {
    Window::getInstance().Close();
    std::cout<<"game closed"<<std::endl;
}

void Game::run() {
    while (Window::getInstance().IsOpen()) { // while the window is open, keep updating and rendering
        Window::getInstance().Clear();
        Update();
        Render();
    }
    Close(); // close the game when the window is closed (i.e. the user closes the window)
}

void Game::Update() {
    m_stateManager->update(); // State manager contains the current state of the game and updates it
}
