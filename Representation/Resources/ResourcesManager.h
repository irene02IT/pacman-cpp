#ifndef INC_2023_PROJECT_IRENE02IT_RESOURCESMANAGER_H
#define INC_2023_PROJECT_IRENE02IT_RESOURCESMANAGER_H
#include "../../Logic/Utilities/Global.h"
#include "SFML/Graphics.hpp"
#include "string"
#include "../../Logic/Map/Grid.h"
#include <array>
#include <vector>

// Enum class for Sprite Types
enum class SpriteType {
    Pacman,
    Fruit,
    RedGhost,
    PinkGhost,
    BlueGhost,
    OrangeGhost,
    ScaredGhost,
    DeadGhost,
    Coin,
    Energizer,
    Banana
};

// Struct managing Sprite Data
struct SpriteData {
    SpriteType sprite;
    sf::Vector2f coord;
};

// Sprite Manager Class that inherits the Resources Manager Class
class SpriteManager {
private:
    sf::Texture wallTexture;
    sf::Texture characterTexture;
    int textureModule = 936 / 18.72;
    // vector containing the sprite data (location on the texture)
    std::vector<SpriteData> sprite_coord_data = { { SpriteType::Pacman, sf::Vector2f(17, 0) },
                                                  { SpriteType::Fruit, sf::Vector2f(12, 0) },
                                                  { SpriteType::RedGhost, sf::Vector2f(13, 0) },
                                                  { SpriteType::PinkGhost, sf::Vector2f(14, 0) },
                                                  { SpriteType::BlueGhost, sf::Vector2f(15, 0) },
                                                  { SpriteType::OrangeGhost, sf::Vector2f(16, 0) },
                                                  { SpriteType::ScaredGhost, sf::Vector2f(0, 11) },
                                                  { SpriteType::DeadGhost, sf::Vector2f(6, 6) },
                                                  { SpriteType::Coin, sf::Vector2f(8, 8) },
                                                  { SpriteType::Energizer, sf::Vector2f(8, 6) },
                                                  { SpriteType::Banana, sf::Vector2f(12, 5) } };
    SpriteManager();
    static SpriteManager* instance; // Unique instance of the class
public:
    static SpriteManager& getInstance(); // Method to get the instance of the class

    // Function handling the creation and cropping of Wall Textures
    sf::Sprite CropWallTexture(std::shared_ptr<Grid> i_map, int a, int b);

    // Function handling the creation and cropping of Sprite Textures
    sf::Sprite CropSpriteTexture(SpriteType spriteType, Direction spriteDirection);
};

#endif // INC_2023_PROJECT_IRENE02IT_RESOURCESMANAGER_H