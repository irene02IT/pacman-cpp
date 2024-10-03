#ifndef INC_2023_PROJECT_IRENE02IT_VISITOR_H
#define INC_2023_PROJECT_IRENE02IT_VISITOR_H


class Cell;
// Visitor interface for the cells. It allows to visit a cell and perform some operation on it.
// It's used by the ShortestPathVisitor to visit each cell in the grid and calculate the shortest path.
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Cell* cell) = 0;
};



#endif //INC_2023_PROJECT_IRENE02IT_VISITOR_H
