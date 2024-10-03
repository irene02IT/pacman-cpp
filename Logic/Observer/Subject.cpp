#include "Subject.h"

void Subject::addObserver(const std::shared_ptr<Observer> &observer)
{
    observers.push_back(observer);
}

void Subject::removeObserver(const std::shared_ptr<Observer> &observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
