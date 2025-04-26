#ifndef STAIR_HPP
#define STAIR_HPP

#include <MapManager.hpp>

#include "Thing.hpp"

class MapManager;

class Stair : public Thing {
public:
    Stair(const std::vector<std::string> &data, const int &x, const int &y, const int &index, MapManager* currentmap) :
    Thing("Stair/" + data[0], true, x, y, index),
    m_Name(data[1]), m_Up(std::stoi(data[2])), m_Down(std::stoi(data[3])), m_SpecificFloor(std::stoi(data[4])),
    m_CurrentMap(currentmap) { }

    void Touched() override;

private:
    std::string m_Name;
    bool m_Up;
    bool m_Down;
    int m_SpecificFloor;
    MapManager* m_CurrentMap;
};

#endif
