#ifndef INC_2023_PROJECT_IRENE02IT_WORLD_H
#define INC_2023_PROJECT_IRENE02IT_WORLD_H

#include <vector>
#include <stack>
#include "../Entities/Collectables/Coin.h"
#include "../Entities/Collectables/Fruit.h"
#include "../Entities/Movables/Ghost/Ghost.h"
#include "../Entities/Movables/Pacman/Pacman.h"
#include "../Entities/Wall.h"
#include "../../Representation/View/ScoreView.h"
#include "../Map/Map.h"


class EntityFactory;

// The world is the class that contains all the entities and the game grid.
// It's the controller that manages what happens between the entities.
// It is responsible for:
// - updating pacman and ghost movement
// - checking for collisions.
// - handling the input from the user
// - creating the entities from the game grid through the entity factory
// - keeping track of the score
// - handling the banana spawning

class World {
private:
    std::shared_ptr<Map> maze_grid; // game grid
    std::shared_ptr<EntityFactory> entity_factory;  // factory to create entities
    std::vector<std::shared_ptr<EntityModel>> m_entities; // contains all the entities in the world (walls, ghosts, pacman, collectables, banana)
    std::shared_ptr<class Pacman> m_pacman; // pacman entity in the world
    std::shared_ptr<Score> m_score;
    Direction m_desiredDirection = Direction::EAST;
    float timeSinceLastBanana = 0.0f;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    std::unordered_map<sf::Keyboard::Key, std::function<void()>> inputMap;

public:
    explicit World(std::shared_ptr<EntityFactory> factory);

    virtual ~World();

    void addEntity(const std::shared_ptr<EntityModel>& entity);

    void updateWorld(float deltaTime);

    void createEntitiesFromMazeGrid();

    void HandleInput(sf::Keyboard::Key input);

    std::vector<std::shared_ptr<EntityModel>> getEntities();

    std::vector<std::shared_ptr<class Wall>> getWalls();

    std::vector<std::shared_ptr<Collectable>> getCollectables();

    std::vector<std::shared_ptr<EntityModel>> getNotWallEntities();

    std::vector<std::shared_ptr<class Ghost>> getGhosts();

    std::shared_ptr<class Pacman> getPacman();

    int getNumberOfAvailableCollectables();

    std::shared_ptr<EntityModel> getEntityAt(float x, float y);

    void move_pacman();

    void move_ghosts();

    bool checkIfWall(Position position);

    void updateScore();

    void tryChangeDirection();

    bool areColliding(const std::shared_ptr<EntityModel>& a, const std::shared_ptr<EntityModel>& b);

    void handleCollision(const std::shared_ptr<EntityModel>& a, const std::shared_ptr<EntityModel>& b);

    bool checkIfGhost(Position position);

    void setGhostsSpawnPoint(Position s_point);

    bool isCrossing(const Position &position);

    void spawnBanana();

    void removeEntityAt(float x, float y);

    void removeEntity(const std::shared_ptr<EntityModel> &entity);

};

#endif // INC_2023_PROJECT_IRENE02IT_WORLD_H
