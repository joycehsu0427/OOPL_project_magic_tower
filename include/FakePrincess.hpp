#ifndef FAKEPRINCESS_HPP
#define FAKEPRINCESS_HPP

#include "Enemy.hpp"
#include "NPC.hpp"
#include "MapManager.hpp"

class FakePrincess : public Enemy{
public:
    FakePrincess(const std::vector<std::string> &enemydata, const std::vector<std::string> &npcdata, const int &floor,
    const int &x, const int &y, const std::shared_ptr<Fighting> &fighting, const std::shared_ptr<NPCDialog> &npcDialog, MapManager *mapManager):
    Enemy(enemydata, x, y, std::stoi(enemydata[15]), fighting), m_MapManager(mapManager) {
        m_NPC = std::make_shared<NPC>(npcdata, floor, x, y, std::stoi(enemydata[15]), npcDialog);
    }

    void Touched() override {
        if (m_Touch == NPCDialogTouch) {
            m_Touch = FightingTouch;
            m_NPC->Touched();
            m_MapManager->FakePrincessStart();
            if (m_Traversable)
                m_Visible = false;
        }
        else if (m_Touch == FightingTouch) {
            m_Touch = NPCDialogTouch;
            m_Fighting->StartFighting(this);
            // Die();
        }
    }

    void Die() override{
        m_Visible = false;
        m_MapManager->FakePrincessEnd();
    }

private:
    enum Touch {
        NPCDialogTouch = 0,
        FightingTouch
    };
    int m_Touch = NPCDialogTouch;
    std::shared_ptr<NPC> m_NPC;
    MapManager *m_MapManager;
};

#endif
