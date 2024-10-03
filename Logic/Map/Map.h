#ifndef INC_2023_PROJECT_IRENE02IT_MAP_H
#define INC_2023_PROJECT_IRENE02IT_MAP_H

#include "../Utilities/Global.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <array>

// Map class that represents the maze. It incapsulates the grid object,
// representing the maze as collection of cells.
// It's responsible for loading the maze from file, assigning the cell types, getting their values
// and providing a link to pathfind functionality (responsibility of the grid object)
// Each time an entity moves, the map is updated to reflect the new position of the entity.
class Map {
private:
    std::shared_ptr<Grid> grid_object; // Grid object that represents the maze structure
    int maze_number;
    std::vector<Position> invalidSpawningLocations; //not valid spawning locations for bananas
    std::vector<Position> ghostSpawningArea; // cells from which ghosts can spawn
public:

    [[nodiscard]] std::shared_ptr<Grid> getGrid() const;

    explicit Map(int mazeNumber);

    // Destructor
    ~Map() {
        std::cout<<"destroying map"<<std::endl;
    };

    [[nodiscard]]bool isInvalidSpawningLocation(float x, float y);

    [[nodiscard]] CellType getCell(int x, int y) const;

    [[nodiscard]] bool isWall(int x, int y) const;

    void setCell(int x, int y, CellType value);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    void LoadMazeFromFile(const std::string& filename);

    Position getDoorPosition();

    [[nodiscard]] int getMazeNumber() const;

    void setMazeNumber(int mazeNumber);

    void setNewMaze(int mazeNumber);

    Position getPacmanPosition();

    void updateEntityPosition(CellType type, Position newPos);

    Position getEntityPosition(CellType type);

    Position getGhostPosition(CellType ghostType);

    std::vector<Cell *> getPathFromTo(Position from, Position to); // calculate path from Cell to Cell, returning a vector of Cells

    void print_path(std::vector<Cell *> path);

    bool isGhostHouse(int x, int y);

};

#endif // INC_2023_PROJECT_IRENE02IT_MAP_H