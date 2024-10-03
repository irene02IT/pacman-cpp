#include "Cell.h"
#include "Visitor/Visitor.h"

Cell::Cell(int x, int y) : x(x), y(y) {}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

void Cell::setX(int x) {
    this->x = x;
}

void Cell::setY(int y) {
    this->y = y;
}

const std::vector<CellType>& Cell::getTypes() const {
    return types;
}

void Cell::addType(CellType type) {
    if (!hasType(type)) {
        types.push_back(type);
    }
}

void Cell::removeType(CellType type) {
    types.erase(std::remove(types.begin(), types.end(), type), types.end());
    if(types.empty()) {
        types.push_back(CellType::Empty);
    }
}

void Cell::clearTypes() {
    types.clear();
    types.push_back(CellType::Empty);
}

bool Cell::hasType(CellType type) const {
    return std::find(types.begin(), types.end(), type) != types.end();
}

void Cell::accept(Visitor* visitor) {
    visitor->visit(this);
}