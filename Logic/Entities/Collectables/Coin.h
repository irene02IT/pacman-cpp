#ifndef INC_2023_PROJECT_IRENE02IT_COIN_H
#define INC_2023_PROJECT_IRENE02IT_COIN_H

#include "Collectable.h"

class Coin : public Collectable {
public:
    Coin()
        : Collectable()
    {
    }

    std::string getEntityType() override {
        return "coin";
    }
};

#endif // INC_2023_PROJECT_IRENE02IT_COIN_H