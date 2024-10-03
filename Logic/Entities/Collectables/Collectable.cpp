
#include "Collectable.h"
#include "../../../Representation/Game/SharedContext/SharedContext.h"

void Collectable::collect() {
    this->m_available = false;
    SharedContext::getInstance().getGameMap()->setCell(m_position.x, m_position.y, CellType::Empty);
}

bool Collectable::isAvailable() const {
    return m_available;
}
