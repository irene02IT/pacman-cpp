#ifndef INC_2023_PROJECT_IRENE02IT_TARGETINGSTRATEGY_H
#define INC_2023_PROJECT_IRENE02IT_TARGETINGSTRATEGY_H

#include "../../../../Utilities/Global.h"
class TargetingStrategy {
protected:
    CellType ghostType;
public:
    explicit TargetingStrategy(CellType ghostType) : ghostType(ghostType) {}
    [[nodiscard]] virtual Position calculateTarget(const Position& ghostPosition, const Position& pacManPosition, const Position& spawnPoint, const Position& startPoint) const = 0;
    virtual ~TargetingStrategy() = default;
};

class SpawningStrategy : public TargetingStrategy {
public:
    explicit SpawningStrategy(CellType ghostType) : TargetingStrategy(ghostType) {}
    [[nodiscard]] Position calculateTarget(const Position& ghostPosition, const Position& pacManPosition, const Position& spawnPoint, const Position& startPoint) const override;
};

class ChasingStrategy : public TargetingStrategy {
public:
    explicit ChasingStrategy(CellType ghostType) : TargetingStrategy(ghostType) {}
    [[nodiscard]] Position calculateTarget(const Position& ghostPosition, const Position& pacManPosition, const Position& spawnPoint, const Position& startPoint) const override;
};

class FearingStrategy : public TargetingStrategy {
public:
    explicit FearingStrategy(CellType ghostType) : TargetingStrategy(ghostType) {}
    [[nodiscard]] Position calculateTarget(const Position& ghostPosition, const Position& pacManPosition, const Position& spawnPoint, const Position& startPoint) const override;
};

class DeadStrategy : public TargetingStrategy {
public:
    explicit DeadStrategy(CellType ghostType) : TargetingStrategy(ghostType) {}
    [[nodiscard]] Position calculateTarget(const Position& ghostPosition, const Position& pacManPosition, const Position& spawnPoint, const Position& startPoint) const override;
};




#endif //INC_2023_PROJECT_IRENE02IT_TARGETINGSTRATEGY_H
