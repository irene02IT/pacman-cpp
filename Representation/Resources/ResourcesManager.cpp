#include "ResourcesManager.h"

// Function handling the creation and cropping of Sprite Textures
sf::Sprite SpriteManager::CropSpriteTexture(SpriteType spriteType, Direction spriteDirection)
{

    sf::Sprite sprite;
    // handle different SpriteTypes and their directions
    if (spriteType == SpriteType::Pacman) {
        // Select the element in the vector with the index specified by Pacman
        SpriteData selectedSpriteData = sprite_coord_data[static_cast<int>(SpriteType::Pacman)];
        int rectLeft = textureModule * selectedSpriteData.coord.x;
        // defining the texture for the direction according to spriteDirection
        int rectRight = textureModule * selectedSpriteData.coord.y;
        switch (spriteDirection) {
            case Direction::EAST:
                rectRight += textureModule;
                break;
            case Direction::WEST:
                rectRight += 7 * textureModule;
                break;
            case Direction::NORTH:
                rectRight += 10 * textureModule;
                break;
            case Direction::SOUTH:
                rectRight += 4 * textureModule;
                break;
            case Direction::NONE:
                break;
        }
        sprite.setTextureRect(sf::IntRect(rectLeft, rectRight, textureModule, textureModule));
        sprite.setTexture(characterTexture);
    }
        // handling spriteSelection for Fruits, Coins and Bananas
    else if (spriteType == SpriteType::Fruit || spriteType == SpriteType::Coin || spriteType == SpriteType::Energizer || spriteType == SpriteType::Banana) {
        SpriteData selectedSpriteData = sprite_coord_data[static_cast<int>(spriteType)];
        int rectLeft = textureModule * selectedSpriteData.coord.x;
        int rectRight = textureModule * selectedSpriteData.coord.y;
        sprite.setTextureRect(sf::IntRect(rectLeft, rectRight, textureModule, textureModule));
        sprite.setTexture(characterTexture);
    }
        // Handle Ghosts Sprite Types
    else if (spriteType == SpriteType::DeadGhost || spriteType == SpriteType::ScaredGhost || spriteType == SpriteType::RedGhost || spriteType == SpriteType::OrangeGhost || spriteType == SpriteType::PinkGhost || spriteType == SpriteType::BlueGhost) {
        SpriteData selectedSpriteData = sprite_coord_data[static_cast<int>(spriteType)];
        int rectLeft = textureModule * selectedSpriteData.coord.x;
        int rectRight = textureModule * selectedSpriteData.coord.y;
        switch (spriteDirection) {
            case Direction::NONE:
                break;
            case Direction::EAST:
                rectRight += textureModule;
                break;
            case Direction::SOUTH:
                rectRight += 3 * textureModule;
                break;
            case Direction::WEST:
                rectRight += 5 * textureModule;
                break;
            case Direction::NORTH:
                rectRight += 7 * textureModule;
                break;
        }
        sprite.setTextureRect(sf::IntRect(rectLeft, rectRight, textureModule, textureModule));
        sprite.setTexture(characterTexture);
    }

    return sprite;
}

// Function handling the creation and cropping of Wall Textures
sf::Sprite SpriteManager::CropWallTexture(std::shared_ptr<Grid> i_map, int a, int b)
{
    sf::Sprite wallSprite;
    wallSprite.setTexture(wallTexture);
    bool down = false;
    bool left = false;
    bool right = false;
    bool up = false;

    // Handle defining the directions and creating the wallSprite texture
    if (b < MAP_HEIGHT - 1) {
        if (i_map->getCell(a, b + 1)->hasType(Wall)) {
            down = true;
        }
    }
    if (a > 0) {
        if (i_map->getCell( a - 1, b)->hasType(Wall)) {
            left = true;
        }
    } else {
        left = true;
    }

    if (a < MAP_WIDTH - 1) {
        if (i_map->getCell(a + 1, b)->hasType(Wall)) {
            right = true;
        }
    } else {
        right = true;
    }

    if (b > 0) {
        if (i_map->getCell(a, b - 1)->hasType(Wall)) {
            up = true;
        }
    }

    // Creating the texture according to the direction
    wallSprite.setTextureRect(sf::IntRect(CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CELL_SIZE, CELL_SIZE));

    return wallSprite;
}

SpriteManager* SpriteManager::instance = nullptr;
SpriteManager::SpriteManager()
        {
            wallTexture.loadFromFile("../" + MAP_TEXTURE_PATH);
            characterTexture.loadFromFile("../" + SPRITES_TEXTURE_PATH);
        }
SpriteManager& SpriteManager::getInstance() {
    if (!instance) {
        instance = new SpriteManager();
    }
    return *instance;
}