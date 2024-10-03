
#ifndef INC_2023_PROJECT_IRENE02IT_BANANAVIEW_H
#define INC_2023_PROJECT_IRENE02IT_BANANAVIEW_H


#include "View.h"
#include "../../Logic/Entities/Banana.h"

class BananaView : public View{
public:
    explicit BananaView(const std::shared_ptr<class Banana>& model)
            : View(model) {}
    void SpriteSetup() override;
};


#endif //INC_2023_PROJECT_IRENE02IT_BANANAVIEW_H
