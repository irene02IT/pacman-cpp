#ifndef INC_2023_PROJECT_IRENE02IT_IENTITYFACTORY_H
#define INC_2023_PROJECT_IRENE02IT_IENTITYFACTORY_H

#include "../Entities/Collectables/Collectable.h"
#include "../Entities/EntityModel.h"

class IEntityFactory {
public:

    virtual std::shared_ptr<EntityModel> createPacman() = 0;

    virtual std::shared_ptr<EntityModel> createGhost(GhostColor c) = 0;

    virtual std::shared_ptr<Collectable> createCoin() = 0;

    virtual std::shared_ptr<Collectable> createFruit() = 0;

    virtual std::shared_ptr<EntityModel> createWall() = 0;
};

#endif // INC_2023_PROJECT_IRENE02IT_IENTITYFACTORY_H