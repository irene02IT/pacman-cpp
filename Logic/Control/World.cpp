#include "World.h"

#include <utility>
#include <unordered_map>
#include <functional>

#include "../../Representation/Entities/ConcreteFactory/EntityFactory.h"
#include "../../Representation/Game/GameState/StateManager.h"
#include "../Utilities/Random.h"

// Each time world is created, it creates all the entities from the maze grid,
// and sets the pacman and the score
World::World(std::shared_ptr<EntityFactory> factory)
    : entity_factory(std::move(factory))
    {
    maze_grid = SharedContext::getInstance().getGameMap();
    createEntitiesFromMazeGrid();
    m_pacman = getPacman();
    m_score = SharedContext::getInstance().getScore();
    //the spawn point is 1 position up the door (grid_y-1)
    setGhostsSpawnPoint({maze_grid->getDoorPosition().x,maze_grid->getDoorPosition().y-1});

    // inizialization of input map with lambda functions
    inputMap[sf::Keyboard::Left] = [this]() { moveLeft(); };
    inputMap[sf::Keyboard::Right] = [this]() { moveRight(); };
    inputMap[sf::Keyboard::Up] = [this]() { moveUp(); };
    inputMap[sf::Keyboard::Down] = [this]() { moveDown(); };
}
// world update function, called every frame by state level
void World::updateWorld(float deltaTime)
{
    timeSinceLastBanana += deltaTime;
    // check all the possible collisions
    for (auto& entity : m_entities) {
        for (auto& otherEntity : m_entities) {
            if (entity != otherEntity && areColliding(entity, otherEntity)) {
                handleCollision(entity, otherEntity);
            }
        }
    }
    // update entities view
    for (auto& entity : m_entities) {
        if (entity)
            entity->notify("update view");
    }

    // Spawn a banana if 10 seconds have passed and there is no other banana. time is reset when pacman slips
    if (timeSinceLastBanana >= 10.0f) {
        bool bananaExists = false;
        for (const auto& entity : m_entities) {
            if (std::dynamic_pointer_cast<class Banana>(entity)) {
                bananaExists = true;
                break;
            }
        }

        if (!bananaExists) {
            spawnBanana();
        }
    }
    move_pacman();
    move_ghosts();
    updateScore();
}
void World::addEntity(const std::shared_ptr<EntityModel>& entity)
{
    m_entities.push_back(entity);
}

void World::removeEntityAt(float x, float y) {
    maze_grid->setCell(x, y, CellType::Empty);
    //let's keep the entity in the world, but we will not render it
}

void World::removeEntity(const std::shared_ptr<EntityModel>& entity) {
    //removeEntityAt(entity->get_position().x, entity->get_position().y);
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
}

void World::move_ghosts() {
    for (auto& ghost : getGhosts()) {
        ghost->update();
    }
}
void World::spawnBanana(){
    auto banana = entity_factory->createBanana();
    if (banana) {
        Position pos = Random::getInstance().generateRandomPosition();
        banana->set_position(pos);
        addEntity(banana);
        maze_grid->setCell(pos.x, pos.y, CellType::Banana);
    } else {
        std::cout << "banana creation failed" << std::endl;
    }
}
void World::createEntitiesFromMazeGrid() {
    for (short x = 0; x < MAP_WIDTH; x++) {
        for (short y = 0; y < MAP_HEIGHT; y++) {
                switch (maze_grid->getCell(x, y)) {
                    case CellType::Wall: {
                        auto wall = entity_factory->createWall();
                        if (wall) {
                            wall->set_position(x, y);
                            addEntity(wall);
                        } else {
                            std::cout << "wall creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::Pacman: {
                        auto pacman = entity_factory->createPacman();
                        if (pacman) {
                            pacman->set_position(x, y);
                            pacman->set_init_position(x, y);
                            addEntity(pacman);
                        } else {
                            std::cout << "pacman creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::RedGhost: {
                        auto ghost = entity_factory->createGhost(GhostColor::Red);
                        if (ghost) {
                            ghost->set_position(x, y);
                            ghost->set_init_position(x, y);
                            addEntity(ghost);
                        } else {
                            std::cout << "RedGhost creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::PinkGhost: {
                        auto ghost = entity_factory->createGhost(GhostColor::Pink);
                        if (ghost) {
                            ghost->set_position(x, y);
                            ghost->set_init_position(x, y);
                            addEntity(ghost);
                        } else {
                            std::cout << "PinkGhost creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::BlueGhost: {
                        auto ghost = entity_factory->createGhost(GhostColor::Blue);
                        if (ghost) {
                            ghost->set_position(x, y);
                            ghost->set_init_position(x, y);
                            addEntity(ghost);
                        } else {
                            std::cout << "BlueGhost creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::OrangeGhost: {
                        auto ghost = entity_factory->createGhost(GhostColor::Orange);
                        if (ghost) {
                            ghost->set_position(x, y);
                            ghost->set_init_position(x, y);
                            addEntity(ghost);
                        } else {
                            std::cout << "OrangeGhost creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::Coin: {
                        auto coin = entity_factory->createCoin();
                        if (coin) {
                            coin->set_position(x, y);
                            addEntity(coin);
                        } else {
                            std::cout << "coin creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::Energizer: {
                        auto energizer = entity_factory->createEnergizer();
                        if (energizer) {
                            energizer->set_position(x, y);
                            addEntity(energizer);
                        } else {
                            std::cout << "energizer creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::Fruit: {
                        auto fruit = entity_factory->createFruit();
                        if (fruit) {
                            fruit->set_position(x, y);
                            addEntity(fruit);
                        } else {
                            std::cout << "fruit creation failed" << std::endl;
                        }
                        break;
                    }
                    case CellType::Empty:
                    case CellType::Door:
                    default:
                        break;
                }

        }
    }
}
std::shared_ptr<class Pacman> World::getPacman()
{
    for (const auto& entity : m_entities) {
        if (auto pacman = std::dynamic_pointer_cast<class Pacman>(entity)) {
            return pacman;
        }
    }
    return nullptr; // return nullptr if no pacman found
}

std::vector<std::shared_ptr<class Wall>> World::getWalls()
{
    std::vector<std::shared_ptr<class Wall>> walls;
    for (const auto& entity : m_entities) {
        if (auto wall = std::dynamic_pointer_cast<class Wall>(entity)) {
            walls.push_back(wall);
        }
    }
    return walls;
}

std::vector<std::shared_ptr<Collectable>> World::getCollectables()
{
    std::vector<std::shared_ptr<Collectable>> collectables;
    for (const auto& entity : m_entities) {
        if (auto collectable = std::dynamic_pointer_cast<Collectable>(entity)) {
            collectables.push_back(collectable);
        }
    }
    return collectables;
}

std::vector<std::shared_ptr<Ghost>> World::getGhosts()
{
    std::vector<std::shared_ptr<Ghost>> ghosts;
    for (const auto& entity : m_entities) {
        if (auto ghost = std::dynamic_pointer_cast<Ghost>(entity)) {
            ghosts.push_back(ghost);
        }
    }
    return ghosts;
}

std::vector<std::shared_ptr<EntityModel>> World::getNotWallEntities()
{
    std::vector<std::shared_ptr<EntityModel>> entities;
    for (auto& entity : m_entities) {
        if (entity && typeid(*entity) != typeid(class Wall)) {
            entities.push_back(entity);
        }
    }
    return entities;
}

std::vector<std::shared_ptr<EntityModel>> World::getEntities()
{
    return m_entities;
}

std::shared_ptr<EntityModel> World::getEntityAt(float x, float y)
{
    Position pos { x, y };
    if (x < MAP_WIDTH && y < MAP_HEIGHT) {
        for (auto& entity : m_entities) {
            if (entity->get_position() == pos)
                return entity;
        }
    }
    return nullptr;
}

//input handling for pacman
void World::HandleInput(sf::Keyboard::Key input) {
    // using a map to call the right function based on the input
    auto it = inputMap.find(input);
    if (it != inputMap.end()) {
        it->second();
    }
}

void World::moveLeft() {
    m_desiredDirection = Direction::WEST;
}

void World::moveRight() {
    m_desiredDirection = Direction::EAST;
}

void World::moveUp() {
    m_desiredDirection = Direction::NORTH;
}

void World::moveDown() {
    m_desiredDirection = Direction::SOUTH;
}

void World::tryChangeDirection()
{
    Direction dir = m_desiredDirection;
    Position pos = m_pacman->get_position();
    switch (dir) {
        case NORTH:
            pos.y -= 1;
            break;
        case SOUTH:
            pos.y += 1;
            break;
        case EAST:
            pos.x += 1;
            break;
        case WEST:
            pos.x -= 1;
            break;
    }

    if (!checkIfWall(pos)) {
        m_pacman->set_direction(m_desiredDirection);
    }
}
// move pacman in the desired direction
void World::move_pacman()
{
    // check if pacman can change direction
    tryChangeDirection();
    Direction dir = m_pacman->get_direction();
    // move pacman in the desired direction, according to the current state
    m_pacman->move(dir);
    // update pacman state data (e.g. if pacman is slipping, update the slipping timer)
    m_pacman->update();
}

//check if wall using maze grid
bool World::checkIfWall(Position position){
    if (position.x < 0 || position.x >= MAP_WIDTH || position.y < 0 || position.y >= MAP_HEIGHT) {
        return true;
    }
    return maze_grid->getCell(position.x, position.y) == CellType::Wall;
}
bool World::isCrossing(const Position& position) {
    int walkableDirections = 0;

    // Check NORTH
    if (!checkIfWall({position.x, position.y - 1})) {
        walkableDirections++;
    }

    // Check SOUTH
    if (!checkIfWall({position.x, position.y + 1})) {
        walkableDirections++;
    }

    // Check EAST
    if (!checkIfWall({position.x + 1, position.y})) {
        walkableDirections++;
    }

    // Check WEST
    if (!checkIfWall({position.x - 1, position.y})) {
        walkableDirections++;
    }

    // A crossing has more than 2 walkable directions
    return walkableDirections > 2;
}

bool World::checkIfGhost(Position position){
    std::shared_ptr<EntityModel> e = getEntityAt(std::round(position.x), std::round(position.y));
    if (auto ghost = std::dynamic_pointer_cast<class Ghost>(e)) {
        return true;
    }
    return false;
}
// dynamic cast usage is justified here because it's necessary to call specific methods of the derived classes
void World::handleCollision(const std::shared_ptr<EntityModel>& a, const std::shared_ptr<EntityModel>& b) {
    std::string typeA = a->getEntityType();
    std::string typeB = b->getEntityType();

    if (typeA == "pacman") {
        if (typeB == "coin") {
            auto coin = std::dynamic_pointer_cast<class Coin>(b);
            if (coin && coin->isAvailable()) {
                m_pacman->take(coin);
                removeEntityAt(b->get_position().x, b->get_position().y);
                m_score->add(COIN_TAKEN_SCORE);
            }
        } else if (typeB == "fruit") {
            auto fruit = std::dynamic_pointer_cast<class Fruit>(b);
            if (fruit && fruit->isAvailable()) {
                m_pacman->eat(fruit);
                removeEntityAt(b->get_position().x, b->get_position().y);
                m_score->add(FRUIT_EATEN_SCORE);
                auto ghosts = getGhosts();
                for (auto& ghost : ghosts) {
                    if (!ghost->isFearing())
                        ghost->switchToState(GhostStateType::Fearing);
                }
            }
        } else if (typeB == "ghost") {
            auto ghost = std::dynamic_pointer_cast<class Ghost>(b);
            if (ghost) {
                if (ghost->isFearing()) {
                    m_pacman->kill(ghost);
                    m_score->add(GHOST_EATEN_SCORE);
                } else {
                    m_pacman->die();
                    ghost->switchToState(GhostStateType::Spawning);
                }
            }
        } else if (typeB == "energizer") {
            auto energizer = std::dynamic_pointer_cast<class Energizer>(b);
            if (energizer && energizer->isAvailable()) {
                m_pacman->take(energizer);
                removeEntityAt(b->get_position().x, b->get_position().y);
                m_score->add(ENERGIZER_TAKEN_SCORE);
                auto ghosts = getGhosts();
                for (auto& ghost : ghosts) {
                    if (!ghost->isFearing())
                        ghost->switchToState(GhostStateType::Fearing);
                }
            }
        } else if (typeB == "wall") {
            m_pacman->stop();
        } else if (typeB == "banana") {
            auto banana = std::dynamic_pointer_cast<class Banana>(b);
            if (banana) {
                m_pacman->slip();
                removeEntity(b);
                timeSinceLastBanana = 0.0f;
            }
        }
    } else if (typeA == "ghost") {
        auto ghost = std::dynamic_pointer_cast<Ghost>(a);
        if (typeB == "pacman") {
            if (ghost) {
                if (ghost->isFearing()) {
                    m_pacman->kill(ghost);
                    m_score->add(GHOST_EATEN_SCORE);
                } else {
                    m_pacman->die();
                    ghost->switchToState(GhostStateType::Spawning);
                }
            }
        } else if (typeB == "wall") {
            ghost->stop_and_change_direction();
        } else if (typeB == "ghost") {
            // no ghost-ghost collision
        }
    }
}
// check if two entities are colliding through their positions and sizes (bounding box collision)
bool World::areColliding(const std::shared_ptr<EntityModel>& a, const std::shared_ptr<EntityModel>& b) {
    Position pa = a->get_position();
    Position pb = b->get_position();
    Size sa = a->get_size();
    Size sb = b->get_size();

    return (pa.x < pb.x + sb.width  &&
            pb.x < pa.x + sa.width  &&
            pa.y < pb.y + sb.height &&
            pb.y < pa.y + sa.height);
}

// get the number of available collectables in the world
int World::getNumberOfAvailableCollectables()
{
    int sum = 0;
    for (const auto& entity : m_entities) {
        if (auto collectable = std::dynamic_pointer_cast<Collectable>(entity)) {
            if (collectable->isAvailable())
                sum++;
        }
    }
    return sum;
}
// update the score in the view
void::World::updateScore(){
    m_score->notify("update view");
}

void World::setGhostsSpawnPoint(Position s_point) {
    for (const auto& entity : m_entities) {
        if (auto ghost = std::dynamic_pointer_cast<Ghost>(entity)) {
            ghost->setSpawnPoint(s_point);
        }
    }
}

World::~World() {
    //maze_grid->getGrid()->printGridWithEntities();
    std::cout << "World destroyed" << std::endl;
}


