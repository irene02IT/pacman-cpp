#include <algorithm>
#include <iostream>
#include <string>
#include <array>

#pragma once

/// Size of a cell
constexpr unsigned int CELL_SIZE = 16;

/// Height of a font
constexpr unsigned int FONT_HEIGHT = CELL_SIZE;

/// Height of a Map
constexpr int MAP_HEIGHT = 21;

/// Width of a Map
constexpr int MAP_WIDTH = 21;

constexpr float FRAME_RATE = 0.01;
/// Speed of Pacman
constexpr float PACMAN_SPEED = 0.04;

/// SLIPPING TIME
constexpr float SLIPPING_DURATION = 1;

/// Speed of a Ghost
constexpr float GHOST_SPEED = 0.1;

constexpr double GHOST_FEARING_SPEED = 0.05;

/// Score taken when a Coin is taken
constexpr int COIN_TAKEN_SCORE = 10;

/// Score taken when an Energizer is eaten
constexpr int ENERGIZER_TAKEN_SCORE = 50;

/// Score taken when a Fruit is eaten
constexpr int FRUIT_EATEN_SCORE = 100;

/// Score taken when a Ghost is eaten
constexpr int GHOST_EATEN_SCORE = 200;

/// Resizing factor for Screen
constexpr float SCREEN_RESIZE = 2;

/// Width of Window
constexpr float WINDOW_WIDTH = CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE;

/// Height of Window
constexpr float WINDOW_HEIGHT = (CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE+100;

constexpr float SCALE_FACTOR = 0.66;

constexpr float WALL_SCALE_X = 3 * SCALE_FACTOR;
constexpr float WALL_SCALE_Y = 3 * SCALE_FACTOR;

constexpr float PACMAN_SCALE_X = 1.3 * SCALE_FACTOR;
constexpr float PACMAN_SCALE_Y =PACMAN_SCALE_X;

constexpr float FRUIT_SCALE_X = 1.0 * SCALE_FACTOR;
constexpr float FRUIT_SCALE_Y = 1.0 * SCALE_FACTOR;

constexpr float COIN_SCALE_X = 1.1 * SCALE_FACTOR;
constexpr float COIN_SCALE_Y = 1.1 * SCALE_FACTOR;

constexpr float ENERGIZER_SCALE_X = COIN_SCALE_X;
constexpr float ENERGIZER_SCALE_Y = COIN_SCALE_Y;

constexpr float GHOST_SCALE_X = PACMAN_SCALE_X;
constexpr float GHOST_SCALE_Y = PACMAN_SCALE_Y;

constexpr float BANANA_SCALE_X = 1.1 * SCALE_FACTOR;
constexpr float BANANA_SCALE_Y= 1.1 * SCALE_FACTOR;

/// Title of the Window
const std::string WINDOW_TITLE = "PACMAN GAME";

/// Path for fonts
const std::string FONT_PATH = "Representation/Resources/fonts/emulogic.ttf";

/// Path for Sprites Texture
const std::string SPRITES_TEXTURE_PATH = "Representation/Resources/media/Textures/Sprites.png";

/// Path for Map Texture
const std::string MAP_TEXTURE_PATH = "Representation/Resources/media/Textures/Map16.png";

/// array of maze paths
const std::array<std::string, 2> MAP_MAZE_PATHS = {"Logic/Map/Maze1.txt", "Logic/Map/Maze2.txt"};

const int MAZES_COUNT = MAP_MAZE_PATHS.size();

const std::string TOP_SCORES_PATH = "Logic/Score/TopScores.txt";

/// fonts size for Heading 1
const unsigned int FONT_SIZE_H1 = 25;

/// fonts size for Heading 2
const unsigned int FONT_SIZE_H2 = 22;

/// fonts size for Paragraph
const unsigned int FONT_SIZE_P = 18;

/// Enum for different types of Cells in the game
enum CellType {
    Door,
    Empty,
    Energizer,
    Coin,
    Wall,
    PinkGhost,
    OrangeGhost,
    RedGhost,
    BlueGhost,
    Pacman,
    Fruit,
    Banana
};
/// Enum for different directions
enum Direction {
    EAST,
    SOUTH,
    WEST,
    NORTH,
    NONE,
};
/** Structure to hold position.
 *
 * Position on the game screen.
 */
struct Position {
    /// x coordinate
    float x;
    /// grid_y coordinate
    float y;
    Position()=default;
    Position(float x, float y) : x(x), y(y) {}

    bool operator==(const Position& i_position) const
    {
        return this->x == i_position.x && this->y == i_position.y;
    }
    /** Overloaded operator!=
     *
     * Check if this position is not equal to i_position
     *
     * @param i_position Another position to compare with
     * @return true if both positions are not equal else false
     */
    bool operator!=(const Position& i_position) const
    {
        return this->x != i_position.x && this->y != i_position.y;
    }

    //overloading operator +=(Position)
    void operator+=(const Position& other) {
        this->x+=other.x;
        this->y+=other.y;
    }

    //overloading operator +(Position)
    Position operator+(const Position& other) const {
        return {this->x+other.x,this->y+other.y};
    }

    //overloading operator *(float)
    Position operator*(const float other) const {
        return {this->x*other,this->y*other};
    }
    //overloading operator *=(float)
    void operator*=(const float other) {
        this->x*=other;
        this->y*=other;
    }

    //overloading operator +=(Direction)
    void operator+=(const Direction& direction) {
        switch(direction){
            case EAST:
                this->x+=1;
                break;
            case SOUTH:
                this->y+=1;
                break;
            case WEST:
                this->x-=1;
                break;
            case NORTH:
                this->y-=1;
                break;
            case NONE:
                break;
        }
    }
    //overloading operator +=(Direction)
    Position operator+(const Direction& direction) {
        switch(direction){
            case EAST:
                this->x+=1;
                break;
            case SOUTH:
                this->y+=1;
                break;
            case WEST:
                this->x-=1;
                break;
            case NORTH:
                this->y-=1;
                break;
            case NONE:
                break;
        }
        return *this;
    }
    [[nodiscard]] float manhattanDistance(const Position& other) const {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }
};

struct Size{
    double width;
    double height;
};


constexpr double WALL_SIZE = 1;
constexpr double PACMAN_SIZE = 1;



/// Enum for different colors of Ghost
enum GhostColor {
    Red,
    Orange,
    Pink,
    Blue
};