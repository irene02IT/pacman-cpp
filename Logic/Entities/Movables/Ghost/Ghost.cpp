#include "Ghost.h"

#include <cmath>
#include <utility>
#include "../../../Utilities/Random.h"

Ghost::Ghost(GhostColor c)
        : EntityModel()
        , color(c), spawned(false), m_strategy(nullptr), accumulatedTime(0), target_position({0,0})
{
    set_direction(EAST); // default direction
    int level = SharedContext::getInstance().getScore()->getLevelReached();
    // increase speed for higher levels, each level increases speed by 25%
    if(level>1)
        speed_multiplier = 1.25;
    speed = GHOST_SPEED*speed_multiplier;
    set_size(1,1);
    initialize(); // initialize ghost state
}


void Ghost::die(){
    switchToState(GhostStateType::Dead);
}

void Ghost::changeDirection() {
    /*
    Direction optimalDir = calculateOptimalDirection(target_position);
    if(is_direction_viable(get_position()+optimalDir))
        set_direction(optimalDir);
    else
        set_direction(Random::generateDirection());
    */
    set_new_direction_based_on_path_to_target();
}
/*
void Ghost::changeDirection() {
    set_direction(Random::generateDirection());
}
 */
void Ghost::stop_and_change_direction(){
    set_position(std::round(m_position.x), std::round(m_position.y));
    Direction newdir = Random::generateDirection();
    while (!is_direction_viable(get_position() + newdir)) {
        newdir = Random::generateDirection();
    }
    set_direction(newdir);
    set_new_position();

    //set_new_position_based_on_path_to_target();
}

GhostColor Ghost::getColor() {
    return color;
}

const Position &Ghost::getInitPosition() {
    return m_init_position;
}
GhostStateType Ghost::getGhostMode() {
    return getCurrentStateType();
}

bool Ghost::isFearing() {
    if(getGhostMode() == GhostStateType::Fearing)
        return true;
    return false;
}

bool Ghost::isChasing() {
    if(getGhostMode() == GhostStateType::Chasing)
        return true;
    return false;
}


void Ghost::emptyStack() {
    if(!m_ghostStates.empty()){
        while (!m_ghostStates.empty()) {
            m_ghostStates.pop();
        }
    }
}

GhostState &Ghost::getCurrentState() {
    return *m_ghostStates.top();
}

GhostStateType Ghost::getCurrentStateType(){
    return getCurrentState().getGhostStateType();
}

void Ghost::pushState(std::unique_ptr<GhostState> state) {
    if(!m_ghostStates.empty()){
        m_ghostStates.top()->exit();
    }
    m_ghostStates.push(std::move(state));
    m_ghostStates.top()->enter();
}

void Ghost::popState() {
    if (!m_ghostStates.empty()) {
        m_ghostStates.top()->exit();
        m_ghostStates.pop();
    }
    if (!m_ghostStates.empty()) {
        m_ghostStates.top()->enter();
    }
}

void Ghost::initialize() {
    while (!m_ghostStates.empty()) {
        m_ghostStates.pop();
    }
    pushState(std::make_unique<GhostState_Spawning>(this));
}

void Ghost::switchToState(GhostStateType newState) {
    GhostStateType currentStateType = m_ghostStates.top()->getGhostStateType();
    switch(newState){
        case GhostStateType::Fearing:
            pushState(std::make_unique<GhostState_Fearing>(this));
            break;
        case GhostStateType::Spawning:
            initialize();
            break;
        case GhostStateType::Chasing: //spawning->chasing
            if(currentStateType==GhostStateType::Spawning)
                pushState(std::make_unique<GhostState_Chasing>(this));
            else //chasing <- fearing
                popState();
            break;
        case GhostStateType::Dead:
            pushState(std::make_unique<GhostState_Dead>(this));
            break;
    }
}

void Ghost::setSpawnPoint(Position s_point) {
    spawn_point = s_point;
}

void Ghost::update(){
    /*
    if(isGhostWithinSpawningArea()&& getCurrentState().getGhostStateType()!=GhostStateType::Spawning){
        switchToState(GhostStateType::Spawning);
    }*/
    update_target_position();
    getCurrentState().update();
}

Position Ghost::getSpawnPoint() {
    return spawn_point;
}


bool Ghost::is_direction_viable(Position new_pos) {
    // Check if the new position is within the map boundaries
    if (new_pos.x < 0 || new_pos.x >= MAP_WIDTH || new_pos.y < 0 || new_pos.y >= MAP_HEIGHT) {
        return false;
    }

    // Check if the new position is a wall
    if (SharedContext::getInstance().getWorld()->checkIfWall(new_pos)) {
        return false;
    }

    // Check if the new position is occupied by another ghost
    if (SharedContext::getInstance().getWorld()->checkIfGhost(new_pos)) {
        return false;
    }

    //check if the new position is a ghost door
    if(SharedContext::getInstance().getGameMap()->getDoorPosition() == new_pos && (isFearing() || isChasing()) ){ // prevent from reentering in spawning area when chasing or fearing
        return false;
    }

    return true;
}

bool Ghost::is_at_crossing() {
    Position pos = get_position();
    return SharedContext::getInstance().getWorld()->isCrossing(pos);
}

// Ghost movement to new position

void Ghost::set_new_position() {
    Position old_position = get_position();
        switch(m_direction){
            case NORTH:
                moveUp();
                break;
            case SOUTH:
                moveDown();
                break;
            case EAST:
                moveRight();
                break;
            case WEST:
                moveLeft();
                break;
            case NONE:
                break;
        }
    // Update entity position in the game map
    SharedContext::getInstance().getGameMap()->getGrid()->moveEntityFromTo(this->getGhostType(), old_position.x, old_position.y, get_position().x, get_position().y);
}


void Ghost::set_speed(float s) {
    speed=s;
}

float Ghost::getAccumulatedTime() const {
    return accumulatedTime;
}

void Ghost::setAccumulatedTime(float accTime) {
    Ghost::accumulatedTime = accTime;
}

// move ghost to new position if possible and update accumulated time for ghost movement
/*
void Ghost::move() {
    // Update accumulated time for ghost movement
    setAccumulatedTime(getAccumulatedTime()+StopWatch::getInstance().getElapsedTime());
    // If accumulated time is greater than frame rate, move ghost to new position
    if(getAccumulatedTime()>FRAME_RATE){
        // Get new position for ghost
        Position new_position = get_position();
        // Move ghost to new position
        new_position+=get_direction();
        moveTo(new_position);
        // Reset accumulated time
        setAccumulatedTime(0);
    }
}
*/

void Ghost::move() {
    // Update accumulated time for ghost movement
    setAccumulatedTime(getAccumulatedTime()+StopWatch::getInstance().getElapsedTime());
    // If accumulated time is greater than frame rate, move ghost to new position
    if(getAccumulatedTime()>FRAME_RATE){
        set_new_position_based_on_path_to_target();
        // Move ghost to new position
        //set_new_position();
        // Reset accumulated time
        setAccumulatedTime(0);
    }
}

void Ghost::moveRandomly(){
    // Update accumulated time for ghost movement
    setAccumulatedTime(getAccumulatedTime()+StopWatch::getInstance().getElapsedTime());
    // If accumulated time is greater than frame rate, move ghost to new position
    if(getAccumulatedTime()>FRAME_RATE){
        // Get new position for ghost
        //Position new_position = get_position();
        // Move ghost to new position
        //new_position+=Random::generateDirection();
        set_new_position();
        // Reset accumulated time
        setAccumulatedTime(0);
    }
}

Direction Ghost::calculateOptimalDirection(const Position& targetPosition) {
    Position currentPosition = get_position();

    // Calculate possible new positions
    Position northPosition = currentPosition;
    northPosition += Direction::NORTH;

    Position southPosition = currentPosition;
    southPosition += Direction::SOUTH;

    Position eastPosition = currentPosition;
    eastPosition += Direction::EAST;

    Position westPosition = currentPosition;
    westPosition += Direction::WEST;

    // Calculate Manhattan distances
    float northDistance = northPosition.manhattanDistance(targetPosition);
    float southDistance = southPosition.manhattanDistance(targetPosition);
    float eastDistance = eastPosition.manhattanDistance(targetPosition);
    float westDistance = westPosition.manhattanDistance(targetPosition);

    // Find the direction with the smallest Manhattan distance
    float minDistance = std::min({northDistance, southDistance, eastDistance, westDistance});

    std::vector<Direction> bestDirections;
    if (minDistance == northDistance) bestDirections.push_back(Direction::NORTH);
    if (minDistance == southDistance) bestDirections.push_back(Direction::SOUTH);
    if (minDistance == eastDistance) bestDirections.push_back(Direction::EAST);
    if (minDistance == westDistance) bestDirections.push_back(Direction::WEST);

    // Randomly select one of the best directions
    return bestDirections[Random::generateIndex(bestDirections.size())];
}

float Ghost::getSpeedMultiplier() const {
    return speed_multiplier;
}

void Ghost::set_init_speed() {
    speed= GHOST_SPEED*speed_multiplier;
}
/*
Direction Ghost::calculateOptimalDirection(const Position& targetPosition) {
    Position currentPosition = get_position();
    int deltaX = targetPosition.x - currentPosition.x;
    int deltaY = targetPosition.grid_y - currentPosition.grid_y;

    if (std::abs(deltaX) > std::abs(deltaY)) {
        if (deltaX > 0) {
            return Direction::EAST;
        } else {
            return Direction::WEST;
        }
    } else {
        if (deltaY > 0) {
            return Direction::SOUTH;
        } else {
            return Direction::NORTH;
        }
    }
}
*/

CellType Ghost::getGhostType() {
    switch (color) {
        case GhostColor::Red:
            return CellType::RedGhost;
        case GhostColor::Pink:
            return CellType::PinkGhost;
        case GhostColor::Blue:
            return CellType::BlueGhost;
        case GhostColor::Orange:
            return CellType::OrangeGhost;
    }
}

void Ghost::set_target_position(Position target) {
    target_position = target;
}

void Ghost::update_target_position() {
    set_target_position(m_strategy->calculateTarget(m_position,SharedContext::getInstance().getGameMap()->getPacmanPosition(),spawn_point,m_init_position));
}

Position Ghost::get_target_position() {
    return target_position;
}

void Ghost::update_path_to_target(std::vector<Cell *> path) {
    path_to_target = std::move(path);
}

std::vector<Cell*> Ghost::get_path_to_target() {
    return path_to_target;
}

void Ghost::set_new_direction_based_on_path_to_target(){
    if(path_to_target.empty()) {
        set_direction(Random::generateDirection());
        return;
    }
    Position next_position{ static_cast<float>(path_to_target.back()->getX()), static_cast<float>(path_to_target.back()->getY()) };
    if(next_position.x > m_position.x)
        set_direction(Direction::EAST);
    else if(next_position.x < m_position.x)
        set_direction(Direction::WEST);
    else if(next_position.y > m_position.y)
        set_direction(Direction::SOUTH);
    else if(next_position.y < m_position.y)
        set_direction(Direction::NORTH);
}

void Ghost::set_new_position_based_on_path_to_target() {
    Position old_position = get_position();
    if (path_to_target.empty()) {
        // If path is empty, recalculate the path to the target
        update_path_to_target(getCurrentState().calc_path_to_target());
        if (path_to_target.empty()) {
            // If still empty, move randomly
            set_direction(Random::generateDirection());
            set_position(get_position() + get_direction());
            return;
        }
    }
    Position next_position{ static_cast<float>(path_to_target.back()->getX()), static_cast<float>(path_to_target.back()->getY()) };
    // Set direction based on the change
    Direction newdir = NONE;
    if (next_position.x > m_position.x)
        newdir = Direction::EAST;
    else if (next_position.x < m_position.x)
        newdir = Direction::WEST;
    else if (next_position.y > m_position.y)
        newdir = Direction::SOUTH;
    else if (next_position.y < m_position.y)
        newdir = Direction::NORTH;
    if (m_direction != newdir)
        set_direction(newdir);
    if(m_position.x == next_position.x && m_position.y == next_position.y)
        path_to_target.pop_back();
    switch (m_direction) {
        case NORTH:
            set_position(get_position().x, get_position().y - 1);
            break;
        case SOUTH:
            set_position(get_position().x, get_position().y + 1);
            break;
        case EAST:
            set_position(get_position().x + 1, get_position().y);
            break;
        case WEST:
            set_position(get_position().x - 1, get_position().y);
            break;
        case NONE:
            break;
    }
    // Update entity position in the game map
    SharedContext::getInstance().getGameMap()->getGrid()->moveEntityFromTo(this->getGhostType(), old_position.x, old_position.y, get_position().x, get_position().y);
}

