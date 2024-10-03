#include "CoinView.h"

void CoinView::SpriteSetup() {
    auto coinModel = std::dynamic_pointer_cast<class Coin>(v_model);
    if (coinModel && coinModel->isAvailable()) {
        float x = coinModel->get_position().x;
        float y = coinModel->get_position().y;
        Direction d = coinModel->get_direction();
        sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::Coin, d);

        Position position{x, y};
        Position convertedPos = Camera::toPixelCoordinates(position);
        sprite.setPosition(convertedPos.x, convertedPos.y);
        sprite.setScale(COIN_SCALE_X, COIN_SCALE_Y);
    }
}
