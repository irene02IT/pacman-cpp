#ifndef INC_2023_PROJECT_IRENE02IT_CAMERA_H
#define INC_2023_PROJECT_IRENE02IT_CAMERA_H


#include "Global.h"
#include <SFML/Graphics.hpp>

class Camera {
public:
    // Camera is a Singleton. This method returns the unique instance of Camera
    [[nodiscard]]
    static Camera& getInstance() {
        static Camera instance;
        return instance;
    }

    [[nodiscard]] static Position toPixelCoordinates(Position gamePosition);

    [[nodiscard]] static Position toGameCoordinates(Position pixelPosition);

    void setWindowSize(float width, float height);

private:
    // Private constructor to prevent instancing
    Camera() : windowWidth(WINDOW_WIDTH), windowHeight(WINDOW_HEIGHT) {}

    // Prevention from copy and assignment
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    float windowWidth;
    float windowHeight;
};


#endif //INC_2023_PROJECT_IRENE02IT_CAMERA_H
