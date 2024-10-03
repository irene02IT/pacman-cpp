#include "Wall.h"

Wall::Wall() : EntityModel()
{
    m_size= {WALL_SIZE,WALL_SIZE};
}

std::string Wall::getEntityType() {
    return "wall";
}

