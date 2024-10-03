#include <thread>
#include "State_Level.h"
#include "StateManager.h"

State_Level::State_Level(StateManager *stateManager) : BaseState(stateManager){
    SetUp();
}

State_Level::~State_Level() {
    std::cout<<"destroying State_Level"<<std::endl;
}

void State_Level::SetUp() {
    CreateWorld();
    StopWatch::getInstance().start();
    m_gameTime = 0;
    // Ensure Score is not reinitialized (preserve from losing data from previous levels)
    if (!SharedContext::getInstance().getScore()) {
        SharedContext::getInstance().setScore(std::make_shared<Score>());
    }
}

void State_Level::ProcessInput() {
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

void State_Level::HandleKeyPress(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::P)
        m_stateManager->setNewState(StateType::Paused, StateType::Level);
    if(key == sf::Keyboard::Right || key == sf::Keyboard::Left || key == sf::Keyboard::Up || key == sf::Keyboard::Down){
        m_world->HandleInput(key);
    }
}
void State_Level::checkVictoryOrGameOver(){
    if (SharedContext::getInstance().getScore()->get_pacman_lives() > 0) {
        if (m_world->getNumberOfAvailableCollectables() == 0) {
            m_stateManager->setNewState(StateType::Victory, StateType::Level);
        }
    }else{
        m_stateManager->setNewState(StateType::GameOver, StateType::Level);
    }
}
void State_Level::update() { // updates are triggered if the elapsed time is greater than the frame duration (1/60)
    const int maxFPS = 60;
    const double frameDuration = 1.0 / maxFPS; // Duration of a frame in seconds

    float elapsedTime = StopWatch::getInstance().getElapsedTime();// time from start

    if (elapsedTime < frameDuration) {
        // If time elapsed is less than the frame duration, sleep for the remaining time
        std::this_thread::sleep_for(std::chrono::duration<double>(frameDuration - elapsedTime));
        elapsedTime = frameDuration; // force elapsed time to be the frame duration
    }

    StopWatch::getInstance().reset(); // reset the stopwatch for the next frame
    m_gameTime += elapsedTime; //update the game time

    //level loop logic:
    checkVictoryOrGameOver(); //if pacman is dead, game over; if all collectables are eaten, victory.
    ProcessInput(); //otherwise, keep going
    m_world->updateWorld(elapsedTime); // and update the world
}

void State_Level::enter() {
    std::cout<<"welcome State_Level"<<std::endl;
}

void State_Level::CreateWorld()
{
    // (the map is already created by STATE_MENU, since it handles the maze selection and map is part of the shared context)
    //creates a new world object with a new EntityFactory to set in the SharedContext (which still may contain the previous
    //world object, since it's singleton, so we need to reset it)
    SharedContext::getInstance().setWorld((std::make_shared<World>(std::make_shared<EntityFactory>())));
    //retrieve the world object from the shared context
    m_world = SharedContext::getInstance().getWorld();
}
