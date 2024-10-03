#ifndef INC_2023_PROJECT_IRENE02IT_GRID_H
#define INC_2023_PROJECT_IRENE02IT_GRID_H


#include <vector>
#include <utility>
#include "Cell.h"
#include "../Entities/Wall.h"
// Grid class provides a 2D grid of cells that is used to represent the game map and its entities,
// providing methods to interact with them and calculate the shortest path between two cells.
// It's updated by the Map class, that encapsulates it and provides the interface to the game logic.
class Grid {
public:
    Grid(int width, int height);

    virtual ~Grid();

    std::vector<Cell*> getNeighbors(Cell* cell);
    Cell* getCell(int x, int y);
    void placeWall(int x, int y);
    [[nodiscard]] bool isWall(int x, int y) const;
    void printGrid();
    int getHeight();
    int getWidth();
    void setCellAt(int x, int y, CellType type);

    void moveEntityFromTo(CellType entity, int x, int y, int newX, int newY);
    void printGridWithEntities();
private:
    int width, height;
    std::vector<std::vector<Cell>> cells;
};


#endif //INC_2023_PROJECT_IRENE02IT_GRID_H
