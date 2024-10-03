#ifndef INC_2023_PROJECT_IRENE02IT_MOVABLE_H
#define INC_2023_PROJECT_IRENE02IT_MOVABLE_H

// Abstract class for movable objects (pacman and ghosts).
// It has the methods to move the object in the four directions at a certain speed
class Movable{
protected:
    float speed;
public:
    Movable() = default;
    virtual ~Movable() = default;
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
};

#endif //INC_2023_PROJECT_IRENE02IT_MOVABLE_H
