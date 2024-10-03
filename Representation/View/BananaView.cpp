#include "BananaView.h"

void BananaView::SpriteSetup() {
    auto bananaModel = std::dynamic_pointer_cast<class Banana>(v_model);
    if (bananaModel && bananaModel->isSpawned()) {
        float x = bananaModel->get_position().x;
        float y = bananaModel->get_position().y;
        Direction d = bananaModel->get_direction();
        sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::Banana, d);

        Position position{x, y};
        Position convertedPos = Camera::toPixelCoordinates(position);
        sprite.setPosition(convertedPos.x, convertedPos.y);
        sprite.setScale(BANANA_SCALE_X, BANANA_SCALE_Y);
    }
}
