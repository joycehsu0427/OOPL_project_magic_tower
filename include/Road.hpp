#ifndef ROAD_HPP
#define ROAD_HPP

#include <string>

#include "Thing.hpp"

class Road : public Thing {
public:
    Road(const std::vector<std::string> &data, const int &x, const int &y, const int &index) :
    Thing({RESOURCE_DIR"/bmp/Road/" + data[IMAGE] + ".bmp"}, true, 200,
        std::stoi(data[TRAVERSABLE]), x, y, index),
    m_ATK(std::stoi(data[ATK])) {
        m_ZIndex = 5;
    }

    Road(const std::vector<std::string> &data, const bool &play, const int &x, const int &y, const int &index) :
    Thing({RESOURCE_DIR"/bmp/Road/" + data[IMAGE] + ".bmp",
        RESOURCE_DIR"/bmp/Road/" + data[IMAGE] + "2.bmp"}, play, 200,
        std::stoi(data[TRAVERSABLE]), x, y, index),
    m_ATK(std::stoi(data[ATK])) {
        m_ZIndex = 5;
    }

    void Touched() override {

    }

private:
    enum DATA {
        IMAGE = 0,
        TRAVERSABLE,
        ATK
    };
    int m_ATK;
};

#endif
