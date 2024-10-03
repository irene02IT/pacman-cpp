#include "PacmanView.h"
void PacmanView::SpriteSetup() {
    float x = v_model->get_position().x;
    float y = v_model->get_position().y;
    m_direction = v_model->get_direction();
    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::Pacman, m_direction);
    Position convertedPos = Camera::toPixelCoordinates({x, y});
    sprite.setPosition(convertedPos.x, convertedPos.y);
    sprite.setScale(PACMAN_SCALE_X,PACMAN_SCALE_Y);
}
