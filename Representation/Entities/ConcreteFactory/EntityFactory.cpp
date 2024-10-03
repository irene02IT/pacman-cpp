
#include "EntityFactory.h"

std::shared_ptr<EntityModel> EntityFactory::createPacman() {
    auto pacman = std::make_shared<class Pacman>(); // creates a shared pointer to a new Pacman object
    auto pacman_view = std::make_shared<PacmanView>(pacman); // creates the view in the same way
    pacman->addObserver(pacman_view); // connects the view to the model, through the observer pattern
    return pacman; // returns the shared pointer to the model
}

std::shared_ptr<EntityModel> EntityFactory::createGhost(GhostColor c) {
    auto ghost = std::make_shared<Ghost>(c);
    auto ghost_view = std::make_shared<GhostView>(ghost, c);
    ghost->addObserver(ghost_view);
    return ghost;
}

std::shared_ptr<Collectable> EntityFactory::createFruit() {
    auto fruit = std::make_shared<class Fruit>();
    auto fruit_view = std::make_shared<FruitView>(fruit);
    fruit->addObserver(fruit_view);
    return fruit;
}

std::shared_ptr<Collectable> EntityFactory::createCoin() {
    auto coin = std::make_shared<class Coin>();
    auto coin_view = std::make_shared<CoinView>(coin);
    coin->addObserver(coin_view);
    return coin;
}

std::shared_ptr<EntityModel> EntityFactory::createWall() {
    auto wall = std::make_shared<class Wall>();
    auto wall_view = std::make_shared<WallView>(wall);
    wall->addObserver(wall_view);
    return wall;
}

std::shared_ptr<Collectable> EntityFactory::createEnergizer() {
    auto energizer = std::make_shared<class Energizer>();
    auto energizer_view = std::make_shared<EnergizerView>(energizer);
    energizer->addObserver(energizer_view);
    return energizer;
}

std::shared_ptr<EntityModel> EntityFactory::createBanana() {
    auto banana = std::make_shared<class Banana>();
    auto banana_view = std::make_shared<BananaView>(banana);
    banana->addObserver(banana_view);
    return banana;
}