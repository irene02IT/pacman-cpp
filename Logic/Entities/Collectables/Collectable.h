#ifndef INC_2023_PROJECT_IRENE02IT_COLLECTABLE_H
#define INC_2023_PROJECT_IRENE02IT_COLLECTABLE_H

#include "../EntityModel.h"

/**
 * @class Collectable
 * @brief Class representing a collectable entity in the game.
 *
 * Collectable is derived from the EntityModel class and has additional attribute `m_available`.
 */
class Collectable : public EntityModel {
protected:
    /*
     * @brief Indicating the availability of the collectable entity.
     *
     * If true, the collectable is currently uncollected and available in the game.
     */
    bool m_available;

public:
    /**
     * @brief Default constructor for Collectable.
     *
     * Initializes EntityModel and sets `m_available` to true, indicating the collectable is initially available.
     */
    Collectable()
        : EntityModel()
        , m_available(true) {};

    /**
     * @brief Method to check if the collectable is currently available.
     *
     * @return `m_available` status of the Collectable.
     */
    bool isAvailable() const;


    /**
     * @brief Method to collect the collectable entity.
     *
     * This method should include game logic required when a collectable is collected.
     * For example, increasing player's score, updating `m_available` to false, etc.
     */
    void collect();
};

#endif // INC_2023_PROJECT_IRENE02IT_COLLECTABLE_H