#ifndef INC_2023_PROJECT_IRENE02IT_WALLVIEW_H
#define INC_2023_PROJECT_IRENE02IT_WALLVIEW_H

#include "../../Logic/Entities/Wall.h"
#include "../Game/SharedContext/SharedContext.h"
#include "View.h"

// WallView class has a shared pointer to the Map class in order to access the game map
// and set the wall sprites in the correct position
class WallView : public View {
public:
  explicit WallView(const std::shared_ptr<class Wall>& model)
      : View(model) {}

  void SpriteSetup() override;
};

#endif // INC_2023_PROJECT_IRENE02IT_WALLVIEW_H
