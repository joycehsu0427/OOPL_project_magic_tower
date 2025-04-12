#include "Stair.hpp"
#include "MapManager.hpp"

void Stair::Touched() {
    if (m_Up)
        m_CurrentMap->NextFloor();
    else if (m_Down)
        m_CurrentMap->PreviousFloor();
    else
        m_CurrentMap->SpecificFloor(m_SpecificFloor);
}