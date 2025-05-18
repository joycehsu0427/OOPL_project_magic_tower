#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include "Player.hpp"
#include "Thing.hpp"
#include "ItemDialog.hpp"

class Item : public Thing {
public:
    Item(const std::vector<std::string> &data, const int &x, const int &y, const int &index, const std::shared_ptr<Player> &player, const std::shared_ptr<ItemDialog> &itemDialog) :
    Thing({RESOURCE_DIR"/bmp/Item/" + data[0] + ".bmp", RESOURCE_DIR"/bmp/Item/" + data[0] + ".bmp"}, false, 100, false, x, y, index),
    m_Level(std::stoi(data[1])), m_HP(std::stoi(data[2])), m_ATK(std::stoi(data[3])), m_DEF(std::stoi(data[4])),
    m_AGI(std::stoi(data[5])), m_EXP(std::stoi(data[6])), m_YellowKey(std::stoi(data[7])), m_BlueKey(std::stoi(data[8])),
    m_RedKey(std::stoi(data[9])), m_Coin(std::stoi(data[10])), m_Weak(std::stoi(data[11])), m_Poison(std::stoi(data[12])), m_Dialog(data[13]),
    m_Player(player), m_ItemDialog(itemDialog) {}

    void Touched() override {
        received();
        m_Visible = false;
        m_ItemDialog->SetDialog(m_Dialog);
        m_ItemDialog->SetVisible(true);
    }

private:
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
    std::string m_Dialog;

    std::shared_ptr<Player> m_Player;
    std::shared_ptr<ItemDialog> m_ItemDialog;

    void received() const {
        if (m_Level != 0)
            m_Player->LevelUp(m_Level);
        if (m_HP != 0)
            m_Player->ChangeHP(m_HP);
        if (m_ATK != 0)
            m_Player->ChangeATK(m_ATK);
        if (m_DEF != 0)
            m_Player->ChangeDEF(m_DEF);
        if (m_AGI != 0)
            m_Player->ChangeAGI(m_AGI);
        if (m_EXP != 0)
            m_Player->ChangeEXP(m_EXP);
        if (m_YellowKey != 0)
            m_Player->ChangeYellowKey(m_YellowKey);
        if (m_BlueKey != 0)
            m_Player->ChangeBlueKey(m_BlueKey);
        if (m_RedKey != 0)
            m_Player->ChangeRedKey(m_RedKey);
        if (m_Coin != 0)
            m_Player->ChangeCoins(m_Coin);
        if (m_Weak)
            m_Player->SetWeak(!m_Weak);
        if (m_Poison)
            m_Player->SetPoison(!m_Poison);

    }
};

#endif
