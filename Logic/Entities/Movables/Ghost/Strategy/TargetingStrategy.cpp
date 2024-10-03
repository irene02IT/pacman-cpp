#include "TargetingStrategy.h"

Position SpawningStrategy::calculateTarget(const Position &ghostPosition, const Position &pacManPosition,
                                           const Position &spawnPoint, const Position &startPoint) const {
    return spawnPoint;
}

Position ChasingStrategy::calculateTarget(const Position &ghostPosition, const Position &pacManPosition,
                                          const Position &spawnPoint, const Position &startPoint) const {
    return pacManPosition;
}

Position FearingStrategy::calculateTarget(const Position &ghostPosition, const Position &pacManPosition,
                                          const Position &spawnPoint, const Position &startPoint) const {
    return {
            ghostPosition.x + (ghostPosition.x - pacManPosition.x),
            ghostPosition.y + (ghostPosition.y - pacManPosition.y)
    };
}

Position
DeadStrategy::calculateTarget(const Position &ghostPosition, const Position &pacManPosition, const Position &spawnPoint,
                              const Position &startPoint) const {
    return startPoint;
}
