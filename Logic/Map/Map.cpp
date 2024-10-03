#include <fstream>
#include "Map.h"
#include "Visitor/ShortestPathVisitor.h"

Map::Map(int mazeNumber) : maze_number(mazeNumber), invalidSpawningLocations(), grid_object(std::make_shared<Grid>(MAP_HEIGHT, MAP_WIDTH)) {
    std::cout << "Loading maze " << mazeNumber << std::endl;
    std::string filename = "../" + MAP_MAZE_PATHS[mazeNumber];
    LoadMazeFromFile(filename);
}

std::shared_ptr<Grid> Map::getGrid() const {
    return grid_object;
}

CellType Map::getCell(int x, int y) const {
    const auto& types = grid_object->getCell(x, y)->getTypes();
    return types.empty() ? CellType::Empty : types.back();
}

void Map::setCell(int x, int y, CellType value) {
    if(value == CellType::Empty) {
        grid_object->getCell(x, y)->clearTypes();
        return;
    }
    grid_object->getCell(x, y)->addType(value);
}

int Map::getWidth() const {
    return MAP_WIDTH;
}

int Map::getHeight() const {
    return MAP_HEIGHT;
}

bool Map::isWall(int x, int y) const {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return false;
    }
    return grid_object->isWall(x, y);
}

void Map::LoadMazeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        int row = 0;
        while (std::getline(file, line)) {
            for (int col = 0; col < line.size(); ++col) {
                switch (line[col]) {
                    case '.':
                        grid_object->setCellAt(col, row, CellType::Coin);
                        break;
                    case '#':
                        //place wall in the grid. It's seen just as an obstacle, it's not the wall entity,
                        // which doesn't interact with the grid
                        grid_object->placeWall(col, row);
                        break;
                    case 'P':
                        grid_object->setCellAt(col, row, CellType::Pacman);
                        break;
                    case '0':
                        grid_object->setCellAt(col, row, CellType::RedGhost);
                        break;
                    case '1':
                        grid_object->setCellAt(col, row, CellType::PinkGhost);
                        break;
                    case '2':
                        grid_object->setCellAt(col, row, CellType::BlueGhost);
                        break;
                    case '3':
                        grid_object->setCellAt(col, row, CellType::OrangeGhost);
                        break;
                    case 'f':
                        grid_object->setCellAt(col, row, CellType::Fruit);
                        break;
                    case 'o':
                        grid_object->setCellAt(col, row, CellType::Energizer);
                        break;
                    case ' ':
                        grid_object->setCellAt(col, row, CellType::Empty);
                        break;
                    case '-':
                        grid_object->setCellAt(col, row, CellType::Door);
                        //memorize the first 3 cells under the door as ghostPrison
                        ghostSpawningArea.emplace_back(static_cast<float>(col + 1), static_cast<float>(row - 1));
                        ghostSpawningArea.emplace_back(static_cast<float>(col + 1), static_cast<float>(row));
                        ghostSpawningArea.emplace_back(static_cast<float>(col + 1), static_cast<float>(row + 1));
                        // and as invalid spawning locations
                        invalidSpawningLocations.emplace_back(static_cast<float>(col + 1), static_cast<float>(row - 1));
                        invalidSpawningLocations.emplace_back(static_cast<float>(col + 1), static_cast<float>(row));
                        invalidSpawningLocations.emplace_back(static_cast<float>(col + 1), static_cast<float>(row + 1));
                        break;
                    case 'x':
                        grid_object->setCellAt(col, row, CellType::Empty);
                        invalidSpawningLocations.emplace_back(static_cast<float>(col), static_cast<float>(row));
                        break;
                    case 'B':
                        grid_object->setCellAt(col, row, CellType::Banana);
                        break;
                    default:
                        grid_object->setCellAt(col, row, CellType::Empty);
                        break;
                }
            }
            row++;
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

Position Map::getPacmanPosition() {
    Position pPos = {0, 0};
    for (int row = 0; row < MAP_HEIGHT; ++row) {
        for (int col = 0; col < MAP_WIDTH; ++col) {
            if (grid_object->getCell(row, col)->hasType(CellType::Pacman)) {
                pPos.x = row;
                pPos.y = col;
                return pPos;
            }
        }
    }
    return pPos;
}

Position Map::getEntityPosition(CellType type) {
    Position pos = {0, 0};
    for (int row = 0; row < MAP_HEIGHT; ++row) {
        for (int col = 0; col < MAP_WIDTH; ++col) {
            if (grid_object->getCell(row, col)->hasType(type)) {
                pos.x = row;
                pos.y = col;
                return pos;
            }
        }
    }
    return pos;
}

void Map::updateEntityPosition(CellType type, Position newPos) {
    Position oldPos = getEntityPosition(type);

    if (grid_object->getCell(newPos.x, newPos.y)->hasType(CellType::Wall)) {
        return;
    }

    grid_object->getCell(oldPos.x, oldPos.y)->removeType(type);
    grid_object->getCell(newPos.x, newPos.y)->addType(type);
}

Position Map::getDoorPosition() {
    Position dPos = {0, 0};
    for (int row = 0; row < MAP_HEIGHT; ++row) {
        for (int col = 0; col < MAP_WIDTH; ++col) {
            if (grid_object->getCell(row, col)->hasType(CellType::Door)) {
                dPos.x = row;
                dPos.y = col;
                return dPos;
            }
        }
    }
    return dPos;
}

int Map::getMazeNumber() const {
    return maze_number;
}

void Map::setMazeNumber(int mazeNumber) {
    maze_number = mazeNumber;
}

void Map::setNewMaze(int mazeNumber) {
    std::string filename = "../" + MAP_MAZE_PATHS[mazeNumber];
    LoadMazeFromFile(filename);
    maze_number = mazeNumber;
}

bool Map::isInvalidSpawningLocation(float x, float y) {
    for (auto &pos : invalidSpawningLocations) {
        if (pos.x == x && pos.y == y) {
            return true;
        }
    }
    return false;
}

Position Map::getGhostPosition(CellType ghostType) {
    Position pos = {0, 0};
    for (int row = 0; row < MAP_HEIGHT; ++row) {
        for (int col = 0; col < MAP_WIDTH; ++col) {
            if (grid_object->getCell(row, col)->hasType(ghostType)) {
                pos.x = row;
                pos.y = col;
                return pos;
            }
        }
    }
    return pos;
}

//calculate path from Cell to Cell, returning a vector of Cells
std::vector<Cell*> Map::getPathFromTo(Position from, Position to){
    from.x = static_cast<int>(from.x);
    from.y = static_cast<int>(from.y);
    Cell* start = grid_object->getCell(from.x, from.y);
    Cell* end = grid_object->getCell(to.x, to.y);
    Grid* grid = grid_object.get();
    ShortestPathVisitor visitor(grid, start, end);
    start->accept(&visitor);
    std::vector<Cell*> path = visitor.getPath();
    //visitor.printGrid();
    //print_path(path);
    return path;
}

void Map::print_path(std::vector<Cell*> path){
    std::cout << "path:" << std::endl;
    for (Cell* cell : path) {
        std::cout << "(" << cell->getX() << ", " << cell->getY() << ")" << std::endl;
    }
}

bool Map::isGhostHouse(int x, int y) {
    for (auto &pos : ghostSpawningArea) {
        if (pos.x == x && pos.y == y) {
            return true;
        }
    }
    return false;
}
