#ifndef INC_2023_PROJECT_IRENE02IT_ENTITYMODEL_H
#define INC_2023_PROJECT_IRENE02IT_ENTITYMODEL_H

#include "../Utilities/Global.h"
#include "../Observer/Subject.h"
#include <memory>
#include <valarray>
#include <chrono>

class EntityModel : public Subject {
protected:
    int grid_x{};
    int grid_y{};
    Position m_position;
    Position m_init_position;
    Direction m_direction;
    Size m_size;
public:
    EntityModel()
        : m_position({ 0, 0 }),
          m_size({0.4,0.4}),
          m_init_position({ 0, 0 }),
          m_direction(NONE)
    {
    }
    EntityModel(int x, int y)
        : grid_x(x),
          grid_y(y),
          m_position({ static_cast<float>(x), static_cast<float>(y) }),
          m_size({0.4,0.4}),
          m_init_position({ static_cast<float>(x), static_cast<float>(y) }),
          m_direction(NONE)
    {
    }
    [[nodiscard]] double interactionRadius() const {
        return sqrt(m_size.width * m_size.width + m_size.height * m_size.height) / 2;
    }

    virtual ~EntityModel() = default;
    virtual void notify(const std::string& message);
    void set_init_position(float i_x, float i_y) { m_init_position = { i_x, i_y }; }
    void set_position(float i_x, float i_y) { m_position = { i_x, i_y }; }
    void set_position(Position pos) { m_position = pos; }

    void set_direction(Direction d) { m_direction = d; }

    Position get_position() { return m_position; }

    Position get_init_position() { return m_init_position; }

    Direction get_direction() { return m_direction; }

    Size get_size(){return m_size;}

    void set_size(Size size){ m_size = size;}
    void set_size(double width, double height){m_size.width = width; m_size.height = height;}

    virtual void update();

    virtual std::string getEntityType()=0;

    [[nodiscard]] int get_grid_x() const { return grid_x; }
    [[nodiscard]] int get_grid_y() const { return grid_y; }

};

#endif // INC_2023_PROJECT_IRENE02IT_ENTITYMODEL_H