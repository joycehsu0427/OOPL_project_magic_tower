#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>

#include "Fighting.hpp"
#include "Thing.hpp"


class Enemy : public Thing {
public:
    Enemy(const std::vector<std::string> &data, const int &x, const int &y, const std::shared_ptr<Fighting> &fighting) : Thing("Enemy/" + data[0], false, x, y),
    m_Name(data[1]), m_HP(std::stoi(data[2])), m_ATK(std::stoi(data[3])), m_DEF(std::stoi(data[4])),
    m_AGI(std::stoi(data[5])), m_EXP(std::stoi(data[6])), m_Coin(std::stoi(data[7])), m_Weak(std::stoi(data[8])),
    m_Poison(std::stoi(data[9])), m_ATK_Time(std::stoi(data[10])), m_Ignore_DEF(std::stoi(data[11])), m_Next_Enemy(std::stoi(data[12])),
    m_Killing_ATK(std::stoi(data[13])), m_Fighting(fighting) {
        m_Image_Path = RESOURCE_DIR"/bmp/Enemy/" + data[0] + ".bmp";
    }


    void Touched() override {
        // m_Visible = false;
        m_Fighting->StartFighting(this);
    }

    void Die() {
        m_Visible = false;
    }

    [[nodiscard]] std::string GetName() const { return m_Name; }
    [[nodiscard]] int GetHP() const { return m_HP; }
    [[nodiscard]] int GetATK() const { return m_ATK; }
    [[nodiscard]] int GetDEF() const { return m_DEF; }
    [[nodiscard]] int GetAGI() const { return m_AGI; }
    [[nodiscard]] int GetEXP() const { return m_EXP; }
    [[nodiscard]] int GetCoin() const { return m_Coin; }
    [[nodiscard]] bool GetWeak() const { return m_Weak; }
    [[nodiscard]] bool GetPoison() const { return m_Poison; }
    [[nodiscard]] int GetATK_Time() const { return m_ATK_Time; }
    [[nodiscard]] int GetIgnore_DEF() const { return m_Ignore_DEF; }
    [[nodiscard]] int GetNextEnemy() const { return m_Next_Enemy; }
    [[nodiscard]] int GetKilling_ATK() const { return m_Killing_ATK; }
    [[nodiscard]] std::string GetImage_Path() const { return m_Image_Path; }

private:
    std::string m_Name;
    int m_HP;                   // 血量
    int m_ATK;                  // 攻擊力
    int m_DEF;                  // 防禦力
    int m_AGI;                  // 敏捷
    int m_EXP;                  // 經驗值
    int m_Coin;                 // 金幣
    bool m_Weak;                // 衰弱攻擊
    bool m_Poison;              // 中毒攻擊
    int m_ATK_Time;             // 攻擊次數
    bool m_Ignore_DEF;          // 忽視防禦
    int m_Next_Enemy;           // 是否有下一位敵人
    int m_Killing_ATK;          // 必殺攻擊

    std::string m_Image_Path;
    std::shared_ptr<Fighting> m_Fighting;
};

#endif
