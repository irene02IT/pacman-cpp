#ifndef INC_2023_PROJECT_IRENE02IT_CELL_H
#define INC_2023_PROJECT_IRENE02IT_CELL_H


#include "../Utilities/Global.h"
#include "Visitor/Visitor.h"

#include <vector>
// Cell class. It represents a cell in the grid. It has a position and a list of cell types
//representing the entities currently in it. In fact in the cell can be present more than one type
// of object (e.g. a coin and a ghost).
// It's encapsulated by the grid object, that contains a collection of cell
// It contains a method to accept a visitor, that will be used to implement the visitor pattern
class Cell {
public:
    Cell(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    [[nodiscard]] const std::vector<CellType>& getTypes() const;
    void addType(CellType type);
    void removeType(CellType type);
    [[nodiscard]] bool hasType(CellType type) const;
    void clearTypes();
    void accept(Visitor *visitor);
private:
    int x, y;
    std::vector<CellType> types;
};


#endif //INC_2023_PROJECT_IRENE02IT_CELL_H
