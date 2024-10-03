#include "Banana.h"

std::string Banana::getEntityType() {
    return "banana";
}

bool Banana::isSpawned() const {
    return spawned;
}

Banana::~Banana() {
    std::cout << "Banana destroyed" << std::endl;
}

Banana::Banana(): EntityModel(), spawned(true) {
    std::cout << "Banana created" << std::endl;
}
