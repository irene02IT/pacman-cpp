#ifndef INC_2023_PROJECT_IRENE02IT_PACMANVIEW_H
#define INC_2023_PROJECT_IRENE02IT_PACMANVIEW_H

#include "../../Logic/Entities/Movables/Pacman/Pacman.h"
#include "View.h"

class PacmanView : public View {
public:
  explicit PacmanView(const std::shared_ptr<class Pacman>& model)
      : View(model) {}
  void SpriteSetup() override;
};

#endif // INC_2023_PROJECT_IRENE02IT_PACMANVIEW_H
