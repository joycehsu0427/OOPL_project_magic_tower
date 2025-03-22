#ifndef ROAD_HPP
#define ROAD_HPP

#include <string>

#include "Thing.hpp"

class Road : public Thing {
public:
    Road(std::vector<std::string> data, int x, int y) : Thing("Road/" + data[0], std::stoi(data[2]), x, y),
    m_Name(data[1]), m_ATK(std::stoi(data[3])) {
        m_ZIndex = 5;
    }

    bool IsTraversable() { return m_Traversable; }

    void Touched() override {

    }

private:
    std::string m_Name;
    int m_ATK;
};

#endif //ROAD_HPP
