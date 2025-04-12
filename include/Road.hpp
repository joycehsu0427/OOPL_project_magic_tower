#ifndef ROAD_HPP
#define ROAD_HPP

#include <string>

#include "Thing.hpp"

class Road : public Thing {
public:
    Road(std::vector<std::string> data, int x, int y) :
    Thing("Road/" + data[0], std::stoi(data[1]), x, y),
    m_ATK(std::stoi(data[2])) {
        m_ZIndex = 5;
    }

    void Touched() override {

    }

private:
    int m_ATK;
};

#endif
