#include "Door.hpp"
#include "MapManager.hpp"

Door::Door(const std::vector<std::string> &data, const int &x, const int &y, const int &index, const std::shared_ptr<Player> &player,
    MapManager* mapmanager) :
Thing({RESOURCE_DIR"/bmp/Door/" + data[IMAGE] + ".bmp",
    RESOURCE_DIR"/bmp/Door/" + data[IMAGE] + "2.bmp", RESOURCE_DIR"/bmp/Door/" + data[IMAGE] + "3.bmp",
    RESOURCE_DIR"/bmp/Door/" + data[IMAGE] + "4.bmp", RESOURCE_DIR"/bmp/Door/" + data[IMAGE] + "5.bmp",
    RESOURCE_DIR"/bmp/Door/no_door.png"}, false, 100, false, x, y, index),
m_Name(data[NAME]), m_YellowKey(std::stoi(data[YELLOWKEY])), m_BlueKey(std::stoi(data[BLUEKEY])), m_RedKey(std::stoi(data[REDKEY])),
m_Player(player), m_MapManager(mapmanager){}

void Door::Touched() {
    if (m_YellowKey != 0) {
        if (m_Player->GetYellowKey() != 0) {
            m_Player->ChangeYellowKey(-1);
            OpenDoor();
        }
    }
    else if  (m_BlueKey != 0) {
        if (m_Player->GetBlueKey() != 0) {
            m_Player->ChangeBlueKey(-1);
            OpenDoor();
        }
    }
    else if (m_RedKey != 0) {
        if (m_Player->GetRedKey() != 0) {
            m_Player->ChangeRedKey(-1);
            OpenDoor();
        }
    }
    else {
        OpenDoor();
    }
}

void Door::OpenDoor() {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->Play();
    m_MapManager->SetOpeningDoor(this);
}
