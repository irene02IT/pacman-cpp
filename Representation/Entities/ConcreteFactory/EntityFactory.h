#ifndef INC_2023_PROJECT_IRENE02IT_ENTITYFACTORY_H
#define INC_2023_PROJECT_IRENE02IT_ENTITYFACTORY_H

#include "../../View/CoinView.h"
#include "../../View/FruitView.h"
#include "../../View/GhostView.h"
#include "../../View/PacmanView.h"
#include "../../View/WallView.h"
#include "../../View/EnergizerView.h"
#include "../../View/BananaView.h"
#include "../../../Logic/Entities/Collectables/Coin.h"
#include "../../../Logic/Entities/Collectables/Fruit.h"
#include "../../../Logic/Entities/Movables/Ghost/Ghost.h"
#include "../../../Logic/Entities/Collectables/Energizer.h"
#include "../../../Logic/AbstractFactory/IEntityFactory.h"
#include "../../../Logic/Entities/Movables/Pacman/Pacman.h"
#include "../../../Logic/Entities/Wall.h"
#include "../../../Logic/Entities/Banana.h"
#include <iostream>
#include <memory>
#include <utility>

// EntityFactory class is a concrete implementation of the IEntityFactory interface.
// It provides methods to create each type of entity in the game,
// returning a shared pointer to the created entity.
class EntityFactory : public IEntityFactory {
public:

    explicit EntityFactory()= default;

    std::shared_ptr<EntityModel> createPacman() override;

    std::shared_ptr<EntityModel> createGhost(GhostColor c) override;

    std::shared_ptr<Collectable> createFruit() override;

    std::shared_ptr<Collectable> createCoin() override;

    std::shared_ptr<EntityModel> createWall() override;

    std::shared_ptr<Collectable> createEnergizer();

    std::shared_ptr<EntityModel> createBanana();
};
#endif // INC_2023_PROJECT_IRENE02IT_ENTITYFACTORY_H