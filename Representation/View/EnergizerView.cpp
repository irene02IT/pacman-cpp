#include "EnergizerView.h"

void EnergizerView::SpriteSetup() {
    auto energizerModel = std::dynamic_pointer_cast<class Energizer>(v_model);
    if (energizerModel && energizerModel->isAvailable()) {
        float x = energizerModel->get_position().x;
        float y = energizerModel->get_position().y;
        Direction d = energizerModel->get_direction();
        sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::Energizer, d);
        Position convertedPos = Camera::toPixelCoordinates({x, y});
        sprite.setPosition(convertedPos.x, convertedPos.y);
        sprite.setScale(ENERGIZER_SCALE_X, ENERGIZER_SCALE_Y);
    }
}
