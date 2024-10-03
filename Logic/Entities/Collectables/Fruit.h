#ifndef INC_2023_PROJECT_IRENE02IT_FRUIT_H
#define INC_2023_PROJECT_IRENE02IT_FRUIT_H

#include "Collectable.h"

class Fruit : public Collectable {
public:

    Fruit() : Collectable() {}

    std::string getEntityType() override {
        return "fruit";
    }
};

#endif // INC_2023_PROJECT_IRENE02IT_FRUIT_H