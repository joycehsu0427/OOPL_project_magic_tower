#ifndef FAKEPRINCESS_HPP
#define FAKEPRINCESS_HPP

#include "Enemy.hpp"
#include "NPC.hpp"

class MapManager;

class FakePrincess : public Enemy, public NPC {
public:
    FakePrincess(const std::vector<std::string> &enemydata, const std::vector<std::string> &npcdata, const int &floor,
    const int &x, const int &y, const std::shared_ptr<Fighting> &fighting, const std::shared_ptr<NPCDialog> &npcDialog, MapManager *mapManager):
    Thing("Enemy/" + enemydata[0], false, x, y, std::stoi(enemydata[15])),
    Enemy(enemydata, x, y, std::stoi(enemydata[15]), fighting),
    NPC(npcdata, floor, x, y, std::stoi(enemydata[15]), npcDialog), m_MapManager(mapManager){}

    void Touched() override {
        if (m_Touch == NPCDialogTouch) {
            m_Touch = FightingTouch;
            m_NPCDialog->SetNPCDialog(m_ImagePath, m_Dialog, m_HaveItem, m_Item, m_Hide, false, this);
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

    void Die() override {
        m_Visible = false;
        m_MapManager->FakePrincessEnd();
    }

private:
    enum Touch {
        NPCDialogTouch = 0,
        FightingTouch
    };
    int m_Touch = NPCDialogTouch;

    MapManager *m_MapManager;
};

#endif
