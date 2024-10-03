
#include "EntityModel.h"

void EntityModel::notify(const std::string &message) {
    if (message == "update view") {
        for (const auto& observer : observers) {
            observer->updateView();
        }
    }
    if (message == "coin taken" || message == "fruit eaten" || message == "ghost killed"||message == "energizer taken") {
        for (const auto &observer: observers) {
            if (observer->isScoreObserver()) {
                observer->updateView();
            }
        }
        if(message == "energizer taken"){
            for (const auto& observer : observers) {
                if(observer->isGhostObserver()){
                    observer->updateView();
                }
            }
        }
    }
}

void EntityModel::update() {
    notify("update view");
}

