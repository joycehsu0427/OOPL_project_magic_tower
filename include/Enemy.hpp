#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>

#include "Fighting.hpp"
#include "Thing.hpp"
#include "Read.hpp"


class Enemy : public Thing {
public:
    Enemy(const std::vector<std::string> &data, const int &x, const int &y, const int &index, const std::shared_ptr<Fighting> &fighting) :
    Thing({RESOURCE_DIR"/bmp/Enemy/" + data[IMAGE] + ".bmp",
        RESOURCE_DIR"/bmp/Enemy/" + data[IMAGE] + "2.bmp"}, true, 400, false, x, y, index),
    m_Name(data[NAME]), m_HP(std::stoi(data[HP])), m_ATK(std::stoi(data[ATK])), m_DEF(std::stoi(data[DEF])),
    m_AGI(std::stoi(data[AGI])), m_EXP(std::stoi(data[EXP])), m_Coin(std::stoi(data[COIN])), m_Weak(std::stoi(data[WEAK])),
    m_Poison(std::stoi(data[POISON])), m_ATK_Time(std::stoi(data[ATKTIME])), m_Ignore_DEF(std::stoi(data[IGNOREDEF])),
    m_Next_Enemy(std::stoi(data[NEXTENEMY])), m_Killing_ATK(std::stoi(data[KILLINGATK])), m_Special(data[SPECIAL]), m_Fighting(fighting) {
        m_Image_Path = {RESOURCE_DIR"/bmp/Enemy/" + data[0] + ".bmp",
        RESOURCE_DIR"/bmp/Enemy/" + data[0] + "2.bmp"};
    }

    void Touched() override {
        m_Fighting->StartFighting(this);
        // Die();
        // m_Visible = false;
    }

    virtual void Die() {
        if (m_Next_Enemy == 0)
            m_Visible = false;
        else {
            std::vector<std::vector<std::string>> enemydata = Read::open_csv(RESOURCE_DIR"/Data/Enemy.csv");
            m_Image_Path = {RESOURCE_DIR"/bmp/Enemy/" + enemydata[m_Next_Enemy][0] + ".bmp",
                RESOURCE_DIR"/bmp/Enemy/" + enemydata[m_Next_Enemy][0] + "2.bmp"};
            SetImage(m_Image_Path, true, 400);
            int next = m_Next_Enemy;
            m_Name = enemydata[next][1];
            m_HP = std::stoi(enemydata[next][2]);
            m_ATK = std::stoi(enemydata[next][3]);
            m_DEF = std::stoi(enemydata[next][4]);
            m_AGI = std::stoi(enemydata[next][5]);
            m_EXP = std::stoi(enemydata[next][6]);
            m_Coin = std::stoi(enemydata[next][7]);
            m_Weak = std::stoi(enemydata[next][8]);
            m_Poison = std::stoi(enemydata[next][9]);
            m_ATK_Time = std::stoi(enemydata[next][10]);
            m_Ignore_DEF = std::stoi(enemydata[next][11]);
            m_Next_Enemy = std::stoi(enemydata[next][12]);
            m_Killing_ATK = std::stoi(enemydata[next][13]);
            m_Special = enemydata[next][14];
        }
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
    [[nodiscard]] std::string GetSpecial() const { return m_Special; }
    [[nodiscard]] std::string GetImage_Path() const { return m_Image_Path[0]; }

protected:
    enum DATA {
        IMAGE = 0,
        NAME,
        HP,
        ATK,
        DEF,
        AGI,
        EXP,
        COIN,
        WEAK,
        POISON,
        ATKTIME,
        IGNOREDEF,
        NEXTENEMY,
        KILLINGATK,
        SPECIAL
    };
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
    std::string m_Special;      // 特殊能力

    std::vector<std::string> m_Image_Path;
    std::shared_ptr<Fighting> m_Fighting;
};

#endif
