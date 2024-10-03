#ifndef INC_2023_PROJECT_IRENE02IT_RANDOM_H
#define INC_2023_PROJECT_IRENE02IT_RANDOM_H

#include "Global.h"
#include "../../Representation/Game/SharedContext/SharedContext.h"
#include <random>

// Class that provides random number generation. It's a singleton class.
// usage of mt19937 as random number generator (Mersenne Twister pseudo-random generator)
class Random {
public:
    Random();

    static Random &getInstance() {
        static Random instance;
        return instance;
    }

    // Generate a random direction (NORTH, SOUTH, EAST, WEST). Useful for ghosts.
    static Direction generateDirection();

    float generateProbability();

    // Generate a random index between 1 and size
    static int generateIndex(int size);

    // Generator of random positions
    Position generateRandomPosition();
private:
    // Random number generator
    std::mt19937 rng;

    // private method because it doesn't check for validity. It's the caller's responsibility
    Position generateRandomPosition_();
};

#endif //INC_2023_PROJECT_IRENE02IT_RANDOM_H