#include "ShortestPathVisitor.h"
#include <queue>
#include <algorithm>

ShortestPathVisitor::ShortestPathVisitor(Grid* grid, Cell* start, Cell* end)
        : grid(grid), start(start), end(end) {
    cameFrom[start] = nullptr;
    costSoFar[start] = 0;
}

// the heuristic function used here is the Manhattan distance between two cells
int ShortestPathVisitor::heuristic(Cell* a, Cell* b) {
    return abs(a->getX() - b->getX()) + abs(a->getY() - b->getY());
}

void ShortestPathVisitor::visit(Cell* cell) {
    // A* algorithm: it uses a priority queue to explore the cell with the lowest cost
    std::priority_queue<std::pair<int, Cell*>, std::vector<std::pair<int, Cell*>>, std::greater<>> frontier;
    frontier.emplace(0, start);

    while (!frontier.empty()) { // While there are cells to explore
        Cell* current = frontier.top().second;  // Get the cell with the lowest cost
        frontier.pop(); // Remove the cell from the queue

        if (current == end) break; // If we reached the end cell, we are done

        for (Cell* next : grid->getNeighbors(current)) { // For each neighbor of the current cell, calculate the cost and update the path if a better one is found
            int newCost = costSoFar[current] + 1; // Assuming uniform cost
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                int priority = newCost + heuristic(next, end);
                frontier.emplace(priority, next);
                cameFrom[next] = current;
            }
        }
    }
}
// return the path from the start cell to the end cell by calling the private method reconstructPath
std::vector<Cell*> ShortestPathVisitor::getPath() {
    return reconstructPath();
}

// Reconstruct the path from the end cell to the start cell
std::vector<Cell*> ShortestPathVisitor::reconstructPath() {
    for (Cell* current = end; current != nullptr; current = cameFrom[current]) {
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// Debugging print function. Print the grid with the path marked with 'X', walls with 'O', and empty cells with '.'
void ShortestPathVisitor::printGrid() {
    for (int y = 0; y < grid->getHeight(); ++y) {
        for (int x = 0; x < grid->getWidth(); ++x) {
            Cell* cell = grid->getCell(x, y);
            if (std::find(path.begin(), path.end(), cell) != path.end()) {
                std::cout << "X ";
            } else if (grid->isWall(x, y)) {
                std::cout << "O ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}