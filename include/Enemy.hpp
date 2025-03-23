#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>

#include "Thing.hpp"

class Enemy : public Thing {
public:
    Enemy(std::vector<std::string> data, int x, int y) : Thing("Enemy/" + data[0], false, x, y),
    m_Name(data[1]), m_HP(std::stoi(data[2])), m_ATK(std::stoi(data[3])), m_DEF(std::stoi(data[4])),
    m_AGI(std::stoi(data[5])), m_EXP(std::stoi(data[6])), m_Coin(std::stoi(data[7])), m_Weak(std::stoi(data[8])),
    m_Poison(std::stoi(data[9])), m_ATK_Time(std::stoi(data[10])), m_Ignore_DEF(std::stoi(data[11])), m_Next_Enemy(data[12]),
    m_Killing_ATK(std::stoi(data[13])) {}


    void Touched() override {
        m_Visible = false;
    }

private:
    int m_Place[2];
    std::string m_Name;
    int m_HP;           // 血量
    int m_ATK;          // 攻擊力
    int m_DEF;          // 防禦力
    int m_AGI;          // 敏捷
    int m_EXP;          // 經驗值
    int m_Coin;         // 金幣
    bool m_Weak;
    bool m_Poison;
    int m_ATK_Time;
    bool m_Ignore_DEF;
    std::string m_Next_Enemy;
    int m_Killing_ATK;
};

#endif
