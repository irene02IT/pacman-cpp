#ifndef INC_2023_PROJECT_IRENE02IT_ENERGIZERVIEW_H
#define INC_2023_PROJECT_IRENE02IT_ENERGIZERVIEW_H


#include "View.h"
#include "../../Logic/Entities/Collectables/Energizer.h"

class EnergizerView : public View{
public:
    explicit EnergizerView(const std::shared_ptr<class Energizer>& model)
            : View(model) {}
    void SpriteSetup() override;

};


#endif //INC_2023_PROJECT_IRENE02IT_ENERGIZERVIEW_H
