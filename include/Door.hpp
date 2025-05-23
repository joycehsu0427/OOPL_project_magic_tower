#ifndef DOOR_HPP
#define DOOR_HPP

#include <string>

#include "Player.hpp"
#include "Thing.hpp"

class MapManager;

class Door : public Thing{
public:
    Door(const std::vector<std::string> &data, const int &x, const int &y, const int &index, const std::shared_ptr<Player> &player,
        MapManager* mapmanager);

    void Touched() override;

private:
    enum DATA {
        IMAGE = 0,
        NAME,
        YELLOWKEY,
        BLUEKEY,
        REDKEY
    };
    std::string m_Name;
    int m_YellowKey;
    int m_BlueKey;
    int m_RedKey;
    std::shared_ptr<Player> m_Player;
    MapManager* m_MapManager;

    void OpenDoor();
};

#endif //DOOR_HPP
