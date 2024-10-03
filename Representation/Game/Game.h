#ifndef PACMAN_PROJECT_IRENE_AUGUST_GAME_H
#define PACMAN_PROJECT_IRENE_AUGUST_GAME_H

#include <memory>
#include <stack>
#include "iostream"

#include "GameState/StateManager.h"
#include "../Window/Window.h"
#include "SharedContext/SharedContext.h"

// Game class is the main class that runs the game and handles the game loop
class Game {
public:
    Game();
    ~Game();
    void run();
    void Setup();
    void Update();
    static void Render();
    static void Close();
private:
    // game encapsulates the state manager
    std::shared_ptr<StateManager> m_stateManager;
};


#endif //PACMAN_PROJECT_IRENE_AUGUST_GAME_H