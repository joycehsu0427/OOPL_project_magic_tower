#ifndef DOOR_HPP
#define DOOR_HPP

#include <string>

#include "Thing.hpp"

class Door : public Thing {
public:
    Door(std::vector<std::string> data, int x, int y) : Thing("Door/" + data[0], false, x, y),
    m_Name(data[1]), m_YellowKey(std::stoi(data[2])), m_BlueKey(std::stoi(data[3])), m_RedKey(std::stoi(data[4])){}

    void Touched() override {

    }

private:
    std::string m_Name;
    int m_YellowKey;
    int m_BlueKey;
    int m_RedKey;
};

#endif //DOOR_HPP
