#include "Grid.h"

Grid::Grid(int width, int height) : width(width), height(height) {
    std::cout << "Grid created" << std::endl;
    cells.resize(height, std::vector<Cell>(width, Cell(0, 0)));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cells[y][x] = Cell(x, y);
        }
    }
}

Grid::~Grid() {
    std::cout << "Grid destroyed" << std::endl;
}

std::vector<Cell*> Grid::getNeighbors(Cell* cell) {
    std::vector<Cell*> neighbors;
    int x = cell->getX();
    int y = cell->getY();
    if (x > 0 && !isWall(x - 1, y)) neighbors.push_back(&cells[y][x - 1]);
    if (x < width - 1 && !isWall(x + 1, y)) neighbors.push_back(&cells[y][x + 1]);
    if (y > 0 && !isWall(x, y - 1)) neighbors.push_back(&cells[y - 1][x]);
    if (y < height - 1 && !isWall(x, y + 1)) neighbors.push_back(&cells[y + 1][x]);
    return neighbors;
}

Cell* Grid::getCell(int x, int y) {
    return &cells[y][x];
}

void Grid::placeWall(int x, int y) {
    cells[y][x].addType(CellType::Wall);
}

bool Grid::isWall(int x, int y) const {
    return cells[y][x].hasType(CellType::Wall);
}

int Grid::getHeight() {
    return height;
}

int Grid::getWidth() {
    return width;
}

void Grid::printGrid() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x].hasType(CellType::Wall)) {
                std::cout << "# ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

void Grid::printGridWithEntities() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x].hasType(CellType::Wall)) {
                std::cout << "# ";
            } else if (cells[y][x].hasType(CellType::Pacman)) {
                std::cout << "P ";
            } else if (cells[y][x].hasType(CellType::RedGhost)) {
                std::cout << "0 ";
            } else if (cells[y][x].hasType(CellType::PinkGhost)) {
                std::cout << "1 ";
            } else if (cells[y][x].hasType(CellType::BlueGhost)) {
                std::cout << "2 ";
            } else if (cells[y][x].hasType(CellType::Coin)) {
                std::cout << ". ";
            } else if (cells[y][x].hasType(CellType::Energizer)) {
                std::cout << "E ";
            } else if (cells[y][x].hasType(CellType::Fruit)) {
                std::cout << "F ";
            } else if (cells[y][x].hasType(CellType::Door)) {
                std::cout << "D ";
            } else if (cells[y][x].hasType(CellType::OrangeGhost)) {
                std::cout << "3 ";
            } else if (cells[y][x].hasType(CellType::Banana)) {
                std::cout << "B ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

void Grid::setCellAt(int x, int y, CellType type) {
    cells[y][x].addType(type);
}

void Grid::moveEntityFromTo(CellType entity, int x, int y, int newX, int newY) {
    cells[y][x].removeType(entity);
    if(cells[y][x].getTypes().empty())
        cells[y][x].addType(CellType::Empty);
    cells[newY][newX].addType(entity);
}

