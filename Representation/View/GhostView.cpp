#include "GhostView.h"

void GhostView::SpriteSetup() {
    float x = v_model->get_position().x;
    float y = v_model->get_position().y;

    Direction d = v_model->get_direction();
    auto ghostModel = std::dynamic_pointer_cast<class Ghost>(v_model);
    if (!ghostModel)
        return;

    GhostStateType currentState = ghostModel->getGhostMode();
    switch (currentState) {
        case GhostStateType::Fearing:
            sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::ScaredGhost, d);
            break;
        case GhostStateType::Chasing:
            switch (g_color) {
                case GhostColor::Red:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::RedGhost, d);
                    break;
                case GhostColor::Pink:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::PinkGhost, d);
                    break;
                case GhostColor::Blue:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::BlueGhost, d);
                    break;
                case GhostColor::Orange:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::OrangeGhost, d);
                    break;
            }
            break;
        case GhostStateType::Spawning:
            // Assume the ghost sprite during spawning is the same as chasing or you can customize it if needed
            switch (g_color) {
                case GhostColor::Red:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::RedGhost, d);
                    break;
                case GhostColor::Pink:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::PinkGhost, d);
                    break;
                case GhostColor::Blue:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::BlueGhost, d);
                    break;
                case GhostColor::Orange:
                    sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::OrangeGhost, d);
                    break;
            }
            break;
        case GhostStateType::Dead:
            sprite = SpriteManager::getInstance().CropSpriteTexture(SpriteType::DeadGhost, d);
            break;
        default:
            // Handle other states if necessary
            break;
    }
    Position convertedPos = Camera::toPixelCoordinates({x, y});
    sprite.setPosition(convertedPos.x, convertedPos.y);
    sprite.setScale(GHOST_SCALE_X, GHOST_SCALE_Y);
}

bool GhostView::isGhostObserver() const {
    return true;
}
