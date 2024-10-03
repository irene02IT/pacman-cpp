#ifndef INC_2023_PROJECT_IRENE02IT_SUBJECT_H
#define INC_2023_PROJECT_IRENE02IT_SUBJECT_H

#include "Observer.h"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

// Subject class from which other classes can inherit to become observable
class Subject {
protected:
    // hold the list of observers
    std::vector<std::shared_ptr<Observer>> observers;

public:
    // add an observer to the list
    void addObserver(const std::shared_ptr<Observer>& observer);

    // remove an observer from the list
    void removeObserver(const std::shared_ptr<Observer>& observer);
};

#endif // INC_2023_PROJECT_IRENE02IT_SUBJECT_H