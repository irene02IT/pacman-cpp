#ifndef INC_2023_PROJECT_IRENE02IT_GHOSTVIEW_H
#define INC_2023_PROJECT_IRENE02IT_GHOSTVIEW_H

#include "../../Logic/Entities/Movables/Ghost/Ghost.h"
#include "View.h"
class GhostView : public View {
private:
  GhostColor g_color;

public:
  GhostView(const std::shared_ptr<class Ghost>& model, GhostColor color)
      : View(model), g_color(color) {}
    bool isGhostObserver() const override;
  void SpriteSetup() override;
};

#endif // INC_2023_PROJECT_IRENE02IT_GHOSTVIEW_H
