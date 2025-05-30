#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP

#include <vector>

#include "Road.hpp"
#include "Thing.hpp"
#include "Door.hpp"
#include "Player.hpp"
#include "Fighting.hpp"
#include "ItemDialog.hpp"
#include "NPCDialog.hpp"
#include "ShopDialog.hpp"
#include "Fly.hpp"

class ScenesManager;

class MapManager {
public:
    MapManager(const std::shared_ptr<Fighting> &fighting, const std::shared_ptr<ItemDialog> &itemDialog,
        const std::shared_ptr<NPCDialog> &npcDialog, const std::shared_ptr<ShopDialog> &shopDialog,
        const std::shared_ptr<Fly> &fly);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> children;
        for (int i = 0; i < m_TopFloor; i++) {
            for (int y = 0; y < 11; y++) {
                for (int x = 0; x < 11; x++) {
                    children.push_back(m_RoadMap[i][y][x]);
                    if (m_ThingMap[i][y][x] != nullptr) {
                        children.push_back(m_ThingMap[i][y][x]);
                    }
                }
            }
        }
        children.push_back(m_Wall);
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                if (m_FakePrincessThingMap[y][x] != nullptr) {
                    children.push_back(m_FakePrincessThingMap[y][x]);
                }

            }
        }
        children.push_back(m_Player);
        return children;
    }

    void StartTower();
    void EndTower() const;
    void ResetTower();

    void NextFloor();
    void PreviousFloor();
    void SpecificFloor(int floornum);

    void FakePrincessStart();
    void FakePrincessEnd();

    void PlayerMoveUp();
    void PlayerMoveDown();
    void PlayerMoveLeft();
    void PlayerMoveRight();

    [[nodiscard]] std::shared_ptr<Player> GetPlayer() const { return m_Player; }
    [[nodiscard]] int GetCurrentFloor() const { return m_CurrentFloor; }
    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Thing>>> GetCurrentMap() const;

    void SetScenesManager(const std::shared_ptr<ScenesManager> &scenesManager);

    [[nodiscard]] bool IsDoorOpening();
    void SetOpeningDoor(Door* door);

private:
    enum ThingType {
        EnemyType = 1,
        ItemType,
        NPCType,
        DoorType,
        StairType,
        ShopType,
        BigEnemyType,
        FakePrincessType
    };

    Door* m_OpeningDoor = nullptr;

    // 處存每格位置的變數
    float start_position_x;
    float start_position_y;
    float position_x[11] = {0};
    float position_y[11] = {0};

    int m_TopFloor = 26;                                        // 最高26層 0~25層
    int m_CurrentFloor = 0;                                     // 當前的樓層
    std::shared_ptr<Road> m_RoadMap[26][11][11];                // [層數][y][x]
    std::shared_ptr<Road> m_CurrentRoadMap[26][11][11];         // [層數][y][x]
    std::shared_ptr<Thing> m_ThingMap[26][11][11];              // [層數][y][x]
    std::shared_ptr<Thing> m_CurrentThingMap[26][11][11];       // [層數][y][x]
    std::shared_ptr<Road> m_Wall;
    std::shared_ptr<Thing> m_FakePrincessThingMap[11][11];   // 打假公主前後地圖變化
    std::pair<int, int> m_StairPosition[2][26];                 // [0] 上樓 [1] 下樓
    std::shared_ptr<Player> m_Player;                           // 角色物件

    // RoadMap裡東西的資料
    std::vector<std::vector<std::string>> m_RoadData;

    // ThingsMap裡東西的資料
    std::vector<std::vector<std::string>> m_EnemyData;          // 100
    std::vector<std::vector<std::string>> m_ItemData;           // 200
    std::vector<std::vector<std::string>> m_NPCData;            // 300
    std::vector<std::vector<std::string>> m_DoorData;           // 400
    std::vector<std::vector<std::string>> m_StairData;          // 500
    std::vector<std::vector<std::string>> m_ShopData;           // 600
    std::vector<std::vector<std::string>> m_BigEnemyData;       // 700
    std::vector<std::vector<std::string>> m_FakePrincessData;   // 800

    std::shared_ptr<ScenesManager> m_ScenesManager;

    std::shared_ptr<Fighting> m_Fighting;
    std::shared_ptr<ItemDialog> m_ItemDialog;
    std::shared_ptr<NPCDialog> m_NPCDialog;
    std::shared_ptr<ShopDialog> m_ShopDialog;
    std::shared_ptr<Fly> m_Fly;

    // 基礎Move function
    void MoveFloor(int pre,int next) ;
    void MovePlayer(int x, int y);

    void BuildRoad(int floor, int x, int y, int index);
    void BuildThing(int floor, int x, int y, int index);

    int m_BigEnemies;
    std::vector<std::shared_ptr<Thing>> m_OtherBigEnemies;

};
#endif
