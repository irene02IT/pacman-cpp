//
// Created by irene on 22/03/24.
//

#ifndef INC_2023_PROJECT_IRENE02IT_ENERGIZER_H
#define INC_2023_PROJECT_IRENE02IT_ENERGIZER_H


#include "Collectable.h"

class Energizer : public Collectable{

public:
    Energizer(): Collectable()
    {
    }

    std::string getEntityType() override {
        return "energizer";
    }
};


#endif //INC_2023_PROJECT_IRENE02IT_ENERGIZER_H
