#ifndef STAIR_HPP
#define STAIR_HPP


#include "Thing.hpp"
#include "MapManager.hpp"

class MapManager;

class Stair : public Thing {
public:
    Stair(const std::vector<std::string> &data, const int &x, const int &y, const int &index, MapManager* currentmap) :
    Thing({RESOURCE_DIR"/bmp/Stair/" + data[IMAGE] + ".bmp",
        RESOURCE_DIR"/bmp/Stair/" + data[IMAGE] + ".bmp"}, false, 100, true, x, y, index),
    m_Name(data[NAME]), m_Up(std::stoi(data[UP])), m_Down(std::stoi(data[DOWN])), m_SpecificFloor(std::stoi(data[SPECIFICFLOOR])),
    m_CurrentMap(currentmap) { }

    void Touched() override;

private:
    enum DATA {
        IMAGE = 0,
        NAME,
        UP,
        DOWN,
        SPECIFICFLOOR
    };
    std::string m_Name;
    bool m_Up;
    bool m_Down;
    int m_SpecificFloor;
    MapManager* m_CurrentMap;
};

#endif
