#include "FruitView.h"
void FruitView::SpriteSetup() {
    auto fruitModel = std::dynamic_pointer_cast<class Fruit>(v_model);
    if (fruitModel && fruitModel->isAvailable()) {
        float x = v_model->get_position().x;
        float y = v_model->get_position().y;
        Direction d = v_model->get_direction();
        sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::Fruit, d);
        Position convertedPos = Camera::toPixelCoordinates({x, y});
        sprite.setPosition(convertedPos.x, convertedPos.y);
        sprite.setScale(FRUIT_SCALE_X, FRUIT_SCALE_Y);
    }
}