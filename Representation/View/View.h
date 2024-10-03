#ifndef INC_2023_PROJECT_IRENE02IT_VIEW_H
#define INC_2023_PROJECT_IRENE02IT_VIEW_H

#include <utility>

#include "../../Logic/Entities/EntityModel.h"
#include "../../Logic/Observer/Observer.h"
#include "../Resources/ResourcesManager.h"
#include "../Game/SharedContext/SharedContext.h"
#include "SFML/Graphics.hpp"
#include "../../Logic/Utilities/Camera.h"
#include "../Window/Window.h"

// Interface for rendering the entities.
// It is an observer of the model, so it can update the appearance of the entity when it is notified.
class View : public Observer {
protected:
  std::shared_ptr<class EntityModel> v_model; // Pointer to the model

  // Encapsulation of the sprite and the texture (sfml objects)
  sf::Texture texture;
  sf::Sprite sprite;

  // Direction of the entity. It is used to flip the sprite in the correct direction
  Direction m_direction{};
public:
  explicit View(std::shared_ptr<EntityModel> model);
  ~View() override = default;
  virtual void SpriteSetup() = 0; // each entity has its own sprite setup
  void updateView() override;
  void reinitializeSprite();
  void Draw();
};

#endif // INC_2023_PROJECT_IRENE02IT_VIEW_H