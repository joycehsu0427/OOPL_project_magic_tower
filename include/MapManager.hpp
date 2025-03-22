#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP

#include <memory>
#include <vector>

#include "Road.hpp"
#include "Thing.hpp"
#include "Player.hpp"

#include "Util/GameObject.hpp"

class MapManager{
public:
    MapManager();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() {
        std::vector<std::shared_ptr<Util::GameObject>> children;
        for (int i = 0; i < 1; i++) { // 要到26層
            for (int y = 0; y < 11; y++) {
                for (int x = 0; x < 11; x++) {
                    children.push_back(m_RoadMap[i][y][x]);
                    if (m_ThingMap[i][y][x] != nullptr) {
                        children.push_back(m_ThingMap[i][y][x]);
                    }
                }
            }
        }
        children.push_back(m_Player);
        return children;
    }

    [[nodiscard]] std::shared_ptr<Player> GetPlayer() const { return m_Player; }

    void StartTower() {
        m_CurrentFloor = 0;
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                m_RoadMap[m_CurrentFloor][y][x]->SetVisible(true);
                if (m_ThingMap[m_CurrentFloor][y][x] != nullptr)
                    m_ThingMap[m_CurrentFloor][y][x]->SetVisible(true);
            }
        }
        m_Player->SetVisible(true);
    }
    void EndTower() {
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                m_RoadMap[m_CurrentFloor][y][x]->SetVisible(false);
                m_ThingMap[m_CurrentFloor][y][x]->SetVisible(false);
            }
        }
        m_Player->SetVisible(false);
    }

    void NextFloor() {
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                m_RoadMap[m_CurrentFloor][y][x]->SetVisible(false);
                m_RoadMap[m_CurrentFloor + 1][y][x]->SetVisible(true);
                m_ThingMap[m_CurrentFloor][y][x]->SetVisible(false);
                m_ThingMap[m_CurrentFloor + 1][y][x]->SetVisible(true);
            }
        }
        m_CurrentFloor++;
    }

    void PreviousFloor() {
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                m_RoadMap[m_CurrentFloor][y][x]->SetVisible(false);
                m_RoadMap[m_CurrentFloor - 1][y][x]->SetVisible(true);
                m_ThingMap[m_CurrentFloor][y][x]->SetVisible(false);
                m_ThingMap[m_CurrentFloor - 1][y][x]->SetVisible(true);
            }
        }
        m_CurrentFloor--;
    }

    void PlayerMoveUp();
    void PlayerMoveDown();
    void PlayerMoveLeft();
    void PlayerMoveRight();

private:
    float start_position_x = 192.5f;
    float start_position_y = -385;
    float position_x[11];
    float position_y[11];

    int m_CurrentFloor = 0;
    std::shared_ptr<Road> m_RoadMap[26][11][11]; // [層數][y][x]
    std::shared_ptr<Thing> m_ThingMap[26][11][11]; // [層數][y][x]
    std::shared_ptr<Player> m_Player;

    // RoadMap裡的東西
    std::vector<std::vector<std::string>> m_RoadData;

    // ThingsMap裡的東西
    std::vector<std::vector<std::string>> m_EnemyData;  // 100
    std::vector<std::vector<std::string>> m_ItemData;   // 200
    std::vector<std::vector<std::string>> m_NPCData;    // 300
    std::vector<std::vector<std::string>> m_DoorData;   // 400
    std::vector<std::vector<std::string>> m_StairData;  // 500
    std::vector<std::vector<std::string>> m_ShopData;   // 600

    void move(int x, int y);

    [[nodiscard]] std::vector<std::vector<std::string>> open_csv(std::string filepath);
    [[nodiscard]] std::vector<std::string> split_csv(std::string line);

};
#endif
