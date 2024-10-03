#ifndef INC_2023_PROJECT_IRENE02IT_OBSERVER_H
#define INC_2023_PROJECT_IRENE02IT_OBSERVER_H

#include <string>
#include <chrono>
#include "../Utilities/Global.h"

// abstract class Observer for the Observer pattern
class Observer {
public:
    virtual ~Observer() = default;

    //virtual methods to be implemented by the concrete observers to check their type

    [[nodiscard]] virtual bool isGhostObserver() const {
        return false;
    }

    [[nodiscard]] virtual bool isScoreObserver() const {
        return false;
    }

    // method to update the view of the observer
    virtual void updateView() = 0;

};

#endif // INC_2023_PROJECT_IRENE02IT_OBSERVER_H