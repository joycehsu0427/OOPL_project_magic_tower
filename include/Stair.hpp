#ifndef STAIR_HPP
#define STAIR_HPP

#include "Thing.hpp"

class Stair : public Thing {
public:
    Stair(std::vector<std::string> data, int x, int y) : Thing("Stair/" + data[0], false, x, y),
    m_Name(data[1]), m_Up(std::stoi(data[2])), m_Down(std::stoi(data[3])), m_SpecialPath(std::stoi(data[4])) {}

    void Touched() override {

    }

private:
    std::string m_Name;
    bool m_Up;
    bool m_Down;
    int m_SpecialPath;
};

#endif
