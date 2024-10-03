#ifndef INC_2023_PROJECT_IRENE02IT_FRUITVIEW_H
#define INC_2023_PROJECT_IRENE02IT_FRUITVIEW_H

#include "../../Logic/Entities/Collectables/Fruit.h"
#include "View.h"
class FruitView : public View {
public:
  explicit FruitView(const std::shared_ptr<class Fruit>& model)
      : View(model) {}
  void SpriteSetup() override;
};

#endif // INC_2023_PROJECT_IRENE02IT_FRUITVIEW_H
