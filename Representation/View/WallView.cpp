#include "WallView.h"

void WallView::SpriteSetup() {
    float x = v_model->get_position().x;
    float y = v_model->get_position().y;
    sprite = SpriteManager::getInstance().CropWallTexture(SharedContext::getInstance().getGameMap()->getGrid(), x, y);
    Position convertedPos = Camera::toPixelCoordinates({x, y});
    sprite.setPosition(convertedPos.x, convertedPos.y);
    sprite.setScale(WALL_SCALE_X, WALL_SCALE_Y);
}