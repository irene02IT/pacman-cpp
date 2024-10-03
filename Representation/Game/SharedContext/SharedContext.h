#ifndef INC_2023_PROJECT_IRENE02IT_SHAREDCONTEXT_H
#define INC_2023_PROJECT_IRENE02IT_SHAREDCONTEXT_H


#include <memory>
#include <utility>
#include "../../../Logic/Control/World.h"

// Singleton class responsible for sharing the context between different parts of the game.
// It is used to encapsulate the parts of the game that need to be globally accessed by different classes or
// whose status needs to be preserved (e.g. when switching state). It doesn't do anything, it just holds pointers.
class SharedContext {
private:
    std::shared_ptr<Map> m_gameMap; // this needs to be globally accessed by the entity models to update their state on the maze
    std::shared_ptr<World> m_world; // world also
    std::shared_ptr<Score>score; // Score needs to be preserved over time, e.g. when the level changes.
    SharedContext();
     ~SharedContext();
public:
    // Delete copy constructor and assignment operator to prevent duplication
    SharedContext(const SharedContext&) = delete;
    SharedContext& operator=(const SharedContext&) = delete;

    // returns the Singleton instance
    static SharedContext& getInstance() {
        static SharedContext instance;
        return instance;
    }

    [[nodiscard]] const std::shared_ptr<Map> &getGameMap() const;

    [[nodiscard]] const std::shared_ptr<World> &getWorld() const;

    [[nodiscard]] const std::shared_ptr<Score> &getScore() const;

    void setGameMap(std::shared_ptr<Map> map);
    void setWorld(std::shared_ptr<World> world);

    void setScore(std::shared_ptr<Score> score_);
    void init();

};
#endif //INC_2023_PROJECT_IRENE02IT_SHAREDCONTEXT_H
