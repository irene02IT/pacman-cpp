#include "Camera.h"

Position Camera::toPixelCoordinates(const Position gamePosition) {
    float x = gamePosition.x * SCREEN_RESIZE * CELL_SIZE;
    float y =  gamePosition.y * SCREEN_RESIZE * CELL_SIZE  ;
    return Position{x,y};
}

Position Camera::toGameCoordinates(const Position pixelPosition) {
    float x = pixelPosition.x / SCREEN_RESIZE/ CELL_SIZE;
    float y = pixelPosition.y / SCREEN_RESIZE/ CELL_SIZE;
    return Position{x,y};
}

void Camera::setWindowSize(float width, float height) {
    windowWidth = width;
    windowHeight = height;
}
