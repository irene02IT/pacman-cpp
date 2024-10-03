#ifndef INC_2023_PROJECT_IRENE02IT_PACMAN_H
#define INC_2023_PROJECT_IRENE02IT_PACMAN_H

#include "../../Collectables/Coin.h"
#include "../../Collectables/Energizer.h"
#include "../../EntityModel.h"
#include "../../Collectables/Fruit.h"
#include "../../../../Representation/Entities/PacmanState/PacmanState.h"
#include "../../../../Representation/Entities/PacmanState/PacmanState_Slipping.h"
#include "../../../../Representation/Entities/PacmanState/PacmanState_Running.h"
#include "../Movable.h"
#include <stack>
#include <chrono>

class Pacman : public EntityModel, public Movable {
public:
    Pacman();
    ~Pacman() override = default;
    static void take(const std::shared_ptr<class Coin>& collectable);
    static void take(const std::shared_ptr<class Energizer>& collectable);
    static void eat(const std::shared_ptr<class Fruit>& collectable);
    void die();
    void kill(const std::shared_ptr<class Ghost>& ghost);
    void move(Direction direction);
    void stop();
    std::string getEntityType() override {
        return "pacman";
    }
    void pushState(std::shared_ptr<PacmanState> pacmanState);
    void popState();
    void switchToState(const std::shared_ptr<PacmanState>& pacmanState);
    void slip();
    bool isSlipping();
    bool isRunning();
    void update() override;

    //----movable functions -----
    void moveUp() override{
        set_direction(NORTH);
        set_position(get_position().x, get_position().y - speed);
    }
    void moveDown() override{
        set_direction(SOUTH);
        set_position(get_position().x, get_position().y + speed);
    }
    void moveLeft() override{
        set_direction(WEST);
        set_position(get_position().x - speed, get_position().y);
    }
    void moveRight() override{
        set_direction(EAST);
        set_position(get_position().x + speed, get_position().y);
    }
private:
    std::stack<std::shared_ptr<PacmanState>> m_pacmanStates;

};

#endif // INC_2023_PROJECT_IRENE02IT_PACMAN_H