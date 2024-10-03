#ifndef INC_2023_PROJECT_IRENE02IT_SHORTESTPATHVISITOR_H
#define INC_2023_PROJECT_IRENE02IT_SHORTESTPATHVISITOR_H


#include "Visitor.h"
#include "../Grid.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <functional>

// Visitor class that implements the A* algorithm to find the shortest path between two cells in the grid.
// It will be used by the ghost entities to find the shortest path to their target cell.
// It uses the Visitor pattern for visiting the cells and the A* algorithm to calculate the shortest path.
class ShortestPathVisitor : public Visitor {
public:
    ShortestPathVisitor(Grid* grid, Cell* start, Cell* end);
    void visit(Cell* cell) override;
    std::vector<Cell*> getPath();
    void printGrid();
private:
    // Raw pointers are used here because the cells are owned by the grid.
    // The grid will delete them when it is destroyed
    Grid* grid;
    Cell* start;
    Cell* end;
    // Unordered maps are used to store the path and the cost to reach each cell.
    // The key is the cell and the value is the cell that came before it in the path.
    // Unordered maps are used because more efficient in insert and search operations.
    std::unordered_map<Cell*, Cell*> cameFrom;
    std::unordered_map<Cell*, int> costSoFar;
    std::vector<Cell*> path; // The final path

    // private methods because they're specific for the class itself (no need to expose it)
    std::vector<Cell*> reconstructPath();
    int heuristic(Cell* a, Cell* b);
};


#endif //INC_2023_PROJECT_IRENE02IT_SHORTESTPATHVISITOR_H
