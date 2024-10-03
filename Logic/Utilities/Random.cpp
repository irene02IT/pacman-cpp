#include "Random.h"

Random::Random(){
    std::cout << "Random class created" << std::endl;
    rng = std::mt19937(std::random_device()());
}

Direction Random::generateDirection() {
    std::uniform_int_distribution<int> dist(0, 3);
    int dir = dist(getInstance().rng);
    switch (dir) {
        case 0: return Direction::NORTH;
        case 1: return Direction::SOUTH;
        case 2: return Direction::EAST;
        case 3: return Direction::WEST;
        default: return Direction::NONE;
    }
}

float Random::generateProbability() {
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng);
}

int Random::generateIndex(int size) {
    std::uniform_int_distribution<int> dist(1, size);
    return dist(getInstance().rng);
}

// Generate a random position within the map and check if it's valid
Position Random::generateRandomPosition() {
    bool valid = false;
    Position pos{};
    //it keeps generating a random position until it's valid (empty and not out of borders)
    while (!valid) {
        pos = generateRandomPosition_(); // call the private method
        CellType name = SharedContext::getInstance().getGameMap()->getCell(pos.x, pos.y);
        bool isOutBorders = SharedContext::getInstance().getGameMap()->isInvalidSpawningLocation(pos.x, pos.y);
        // check if the position is empty and not out of borders
        if(name == CellType::Empty && !isOutBorders){
            valid= true;
        }
    }
    return pos;
}
// generate a random position
Position Random::generateRandomPosition_() {
    std::uniform_int_distribution<int> distX(1, MAP_WIDTH - 2);
    std::uniform_int_distribution<int> distY(1, MAP_HEIGHT - 2);
    return {static_cast<float>(distX(rng)), static_cast<float>(distY(rng))};
}



