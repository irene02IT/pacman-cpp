#ifndef INC_2023_PROJECT_IRENE02IT_WALL_H
#define INC_2023_PROJECT_IRENE02IT_WALL_H

#include "EntityModel.h"

// Wall entity class. It doesn't interact with the grid, it just serves to represent the walls in the game
// through its view implementation
class Wall : public EntityModel {
public:
    Wall();
    std::string getEntityType() override;
};

#endif // INC_2023_PROJECT_IRENE02IT_WALL_H
