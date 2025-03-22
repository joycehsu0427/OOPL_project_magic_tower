#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include "Thing.hpp"

class Item : public Thing {
public:
    Item(std::vector<std::string> data, int x, int y) : Thing("Item/" + data[0], false, x, y),
    m_Level(std::stoi(data[1])), m_HP(std::stoi(data[2])), m_ATK(std::stoi(data[3])), m_DEF(std::stoi(data[4])),
    m_AGI(std::stoi(data[5])), m_EXP(std::stoi(data[6])), m_YellowKey(std::stoi(data[7])), m_BlueKey(std::stoi(data[8])),
    m_RedKey(std::stoi(data[9])), m_Coin(std::stoi(data[10])), m_Weak(std::stoi(data[11])), m_Poison(std::stoi(data[12])) {}

    void Touched() override {

    }

private:
    std::shared_ptr<Player> m_Player;
    // 需要m_Name
    int m_Level;
    int m_HP;
    int m_ATK;
    int m_DEF;
    int m_AGI;
    int m_EXP;
    int m_YellowKey;
    int m_BlueKey;
    int m_RedKey;
    int m_Coin;
    bool m_Weak;
    bool m_Poison;
};

#endif
