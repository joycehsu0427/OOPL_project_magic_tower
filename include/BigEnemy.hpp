#ifndef BIGENEMY_HPP
#define BIGENEMY_HPP

#include "Enemy.hpp"
#include "Util/Logger.hpp"

class BigEnemy : public Enemy {
public:
    BigEnemy(const std::vector<std::string> &data, const int &x, const int &y, const std::shared_ptr<Fighting> &fighting)  :
    Enemy(data, x, y, std::stoi(data[15]), fighting) {}

    void Touched() override {
        if (m_Index != 0) {
            m_Fighting->StartFighting(this);
            // Die();
        }
    }

    void Die() override {
        m_Visible = false;
        for (auto &otherenemy : m_OtherEnemies) {
            otherenemy->SetVisible(false);
        }
    }

    void SetOtherEnemy(const std::vector<std::shared_ptr<Thing>> &otherenemies) {
        m_OtherEnemies = otherenemies;
    }

private:
    std::vector<std::shared_ptr<Thing>> m_OtherEnemies = std::vector<std::shared_ptr<Thing>>();
};

#endif
