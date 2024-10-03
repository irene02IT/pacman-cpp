#ifndef INC_2023_PROJECT_IRENE02IT_BANANA_H
#define INC_2023_PROJECT_IRENE02IT_BANANA_H


#include "EntityModel.h"

// Banana is not a collectable fruit, it's just a simple type of entity
class Banana : public EntityModel {
public:
    Banana();

    ~Banana() override;

    std::string getEntityType() override;

    [[nodiscard]] bool isSpawned() const;

private:
    bool spawned;
};


#endif //INC_2023_PROJECT_IRENE02IT_BANANA_H
