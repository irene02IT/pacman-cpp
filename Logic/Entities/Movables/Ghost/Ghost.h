#ifndef INC_2023_PROJECT_IRENE02IT_GHOST_H
#define INC_2023_PROJECT_IRENE02IT_GHOST_H

#include <stack>
#include <utility>
#include "../../EntityModel.h"
#include "../../../../Representation/Entities/GhostState/GhostState.h"
#include "../../../../Representation/Entities/GhostState/GhostState_Chasing.h"
#include "../../../../Representation/Entities/GhostState/GhostState_Fearing.h"
#include "../../../../Representation/Entities/GhostState/GhostState_Spawning.h"
#include "../../../../Representation/Entities/GhostState/GhostState_Dead.h"
#include "Strategy/TargetingStrategy.h"
#include "../Movable.h"

/**
 * @class Ghost
 *
 * @brief Concrete implementation for Ghost model
 *
 * This class provides the Ghost attributes and behavior for the game.
 * It extends from the EntityModel class and has additional specific properties such
 * as its speed and a flag indicating whether it is fearing or not.
 */

class Ghost : public EntityModel, public Movable {
private:
    float speed_multiplier = 1;
    GhostColor color;
    Position spawn_point;
    std::stack<std::shared_ptr<GhostState>> m_ghostStates;
    bool spawned;
    float accumulatedTime=0;
    std::shared_ptr<TargetingStrategy> m_strategy;
    Position target_position;
    std::vector<Cell *> path_to_target{};
public:
    explicit Ghost(GhostColor color);

    void set_speed(float s);
    void set_strategy(std::shared_ptr<TargetingStrategy> strategy){
        this->m_strategy = std::move(strategy);
    }

    bool isFearing();

    bool isChasing();


    [[nodiscard]] bool isSpawned() const{return spawned;}

    void setSpawned(bool v){spawned = v;}

    void setSpawnPoint(Position s_point);

    Position getSpawnPoint();

    float getAccumulatedTime() const;

    void setAccumulatedTime(float accTime);
    float getSpeedMultiplier() const;
    std::string getEntityType() override {
        return "ghost";
    }
    void die();
    [[nodiscard]] float get_speed() const{return speed;}
    void update() override;

    void changeDirection();

    GhostColor getColor();

    GhostStateType getGhostMode();

    void stop_and_change_direction();

    void emptyStack();

    GhostState& getCurrentState();
    GhostStateType getCurrentStateType();

    void pushState(std::unique_ptr<GhostState>state);

    void popState();

    void initialize();

    void switchToState(GhostStateType newState);

    //ghost movement

    bool is_direction_viable(Position new_pos);

    void set_new_position();

    void move();

    const Position &getInitPosition();

    Direction calculateOptimalDirection(const Position &targetPosition);

    bool is_at_crossing();

    void set_init_speed();

    CellType getGhostType();

    void set_target_position(Position target);

    Position get_target_position();

    void update_target_position();

    void update_path_to_target(std::vector<Cell *> path);

// ------ movable functions ------
    void moveUp() override{
        set_position(get_position().x, get_position().y - speed);
    }
    void moveDown() override{
        set_position(get_position().x, get_position().y + speed);
    }
    void moveLeft() override{
        set_position(get_position().x - speed, get_position().y);
    }
    void moveRight() override{
        set_position(get_position().x + speed, get_position().y);
    }

    void set_new_direction_based_on_path_to_target();

    std::vector<Cell *> get_path_to_target();

    void set_new_position_based_on_path_to_target();

    void moveRandomly();

    bool isGhostWithinSpawningArea();
};

#endif // INC_2023_PROJECT_IRENE02IT_GHOST_H