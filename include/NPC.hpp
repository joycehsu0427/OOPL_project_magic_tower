#ifndef NPC_HPP
#define NPC_HPP

#include <string>

#include "Thing.hpp"

class NPC : public Thing {
public:
    NPC(std::vector<std::string> data, int floor, int x, int y) : Thing("NPC/" + data[0], false, x, y),
    m_Name(data[1]), m_DialogPath(data[2]) {
        m_DialogPath = std::to_string(floor) + "_" + m_Path;
    }

    void Touched() override {

    }

private:
    std::string m_Name;
    std::string m_DialogPath;
};

#endif
