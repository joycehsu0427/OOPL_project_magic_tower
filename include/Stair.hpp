#ifndef STAIR_HPP
#define STAIR_HPP

#include "Thing.hpp"

class Stair : public Thing {
public:
    Stair(std::vector<std::string> data, int x, int y/*, std::shared_ptr<MapManager> mapmanager*/) :
    Thing("Stair/" + data[0], false, x, y),
    m_Name(data[1]), m_Up(std::stoi(data[2])), m_Down(std::stoi(data[3])), m_SpecificPath(std::stoi(data[4]))
    /*, m_MapManager(mapmanager)*/{}

    // void SetMapManager(std::weak_ptr<MapManager> &mapManager) { m_MapManager = mapManager; }

    void Touched() override {
        // if (auto mapmanager = m_MapManager.lock()) {  // 嘗試取得 shared_ptr
        //     if (m_Up)
        //         mapmanager->NextFloor();
        //     else if (m_Down)
        //         mapmanager->PreviousFloor();
        //     else {
        //         mapmanager->SpecificPath(m_SpecificPath);
        //     }
        // }
    }

private:
    std::string m_Name;
    bool m_Up;
    bool m_Down;
    int m_SpecificPath;
    // std::weak_ptr<MapManager> m_MapManager;
};

#endif
