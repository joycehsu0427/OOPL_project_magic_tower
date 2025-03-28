#ifndef STAIR_HPP
#define STAIR_HPP

#include "Thing.hpp"

class Stair : public Thing {
public:
    Stair(std::vector<std::string> data, int x, int y) :
    Thing("Stair/" + data[0], false, x, y),
    m_Name(data[1]), m_Up(std::stoi(data[2])), m_Down(std::stoi(data[3])), m_SpecificFloor(std::stoi(data[4]))
    /*, m_MapManager(mapmanager)*/{}

    void SetMapManager(const std::weak_ptr<MapManager> &mapManager) { m_MapManager = mapManager; }

    void Touched() override {
        if (auto mapmanager = m_MapManager.lock()) {  // 嘗試取得 shared_ptr
            if (m_Up)
                mapmanager->NextFloor();
            else if (m_Down)
                mapmanager->PreviousFloor();
            else {
                mapmanager->SpecificFloor(m_SpecificFloor);
            }
        }
    }

private:
    std::string m_Name;
    bool m_Up;
    bool m_Down;
    int m_SpecificFloor;
    std::weak_ptr<MapManager> m_MapManager;
};

#endif
