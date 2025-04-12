#ifndef DOOR_HPP
#define DOOR_HPP

#include <string>

#include "Player.hpp"
#include "Thing.hpp"

class Door : public Thing /* , public std::enable_shared_from_this<Door> */{
public:
    Door(std::vector<std::string> data, int x, int y, std::shared_ptr<Player> &player) : Thing("Door/" + data[0], false, x, y),
    m_Name(data[1]), m_YellowKey(std::stoi(data[2])), m_BlueKey(std::stoi(data[3])), m_RedKey(std::stoi(data[4])), m_Player(player){}

    void Touched() override {
        if (m_YellowKey != 0) {
            if (m_Player->GetYellowKey() != 0) {
                m_Player->ChangeYellowKey(-1);
                m_Visible = false;
            }
        }
        else if  (m_BlueKey != 0) {
            if (m_Player->GetBlueKey() != 0) {
                m_Player->ChangeBlueKey(-1);
                m_Visible = false;
            }
        }
        else if (m_RedKey != 0) {
            if (m_Player->GetRedKey() != 0) {
                m_Player->ChangeRedKey(-1);
                m_Visible = false;
            }
        }
        else
            m_Visible = false;
    }

private:
    std::string m_Name;
    int m_YellowKey;
    int m_BlueKey;
    int m_RedKey;
    std::shared_ptr<Player> m_Player;
};

#endif //DOOR_HPP
