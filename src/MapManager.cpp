#include <fstream>
#include <sstream>
#include <memory>

#include "MapManager.hpp"

#include "Enemy.hpp"
#include "Item.hpp"
#include "NPC.hpp"
#include "Door.hpp"
#include "Stair.hpp"
#include "Shop.hpp"
#include "BigEnemy.hpp"
#include "FakePrincess.hpp"
#include "ScenesManager.hpp"
#include "Read.hpp"

#include "Util/Logger.hpp"

MapManager::MapManager(const std::shared_ptr<Fighting> &fighting, const std::shared_ptr<ItemDialog> &itemDialog,
    const std::shared_ptr<NPCDialog> &npcDialog, const std::shared_ptr<ShopDialog> &shopDialog,
    const std::shared_ptr<Fly> &fly) : m_Fighting(fighting), m_ItemDialog(itemDialog), m_NPCDialog(npcDialog),
    m_ShopDialog(shopDialog), m_Fly(fly) {
    // xy軸位置設置
    start_position_x = 192.5f;
    start_position_y = -385;
    for (int i = 0; i < 11; i++) {
        position_x[i] = start_position_x - i * 77.0f;
        position_y[i] = start_position_y + i * 77.0f;
    }

    //m_Player 初始化
    m_Player = std::make_shared<Player> (position_x[5], position_y [10], 5, 10);
    m_Player->SetVisible(false);

    // 載入基本資料
    m_EnemyData = Read::open_csv(RESOURCE_DIR"/Data/Enemy.csv");
    m_ItemData = Read::open_csv(RESOURCE_DIR"/Data/Item.csv");
    m_NPCData = Read::open_csv(RESOURCE_DIR"/Data/NPC.csv");
    m_DoorData = Read::open_csv(RESOURCE_DIR"/Data/Door.csv");
    m_StairData = Read::open_csv(RESOURCE_DIR"/Data/Stair.csv");
    m_ShopData = Read::open_csv(RESOURCE_DIR"/Data/Shop.csv");
    m_BigEnemyData = Read::open_csv(RESOURCE_DIR"/Data/BigEnemy.csv");;
    m_FakePrincessData = Read::open_csv(RESOURCE_DIR"/Data/FakePrincess.csv");
    m_RoadData = Read::open_csv(RESOURCE_DIR"/Data/Road.csv");

    // 載入FakePrincessRoad / ThingsMap
    m_Wall = std::make_shared<Road>(m_RoadData[4], position_x[5], position_y[2], 4);
    std::vector<std::vector<std::string> > ThingsMapData = Read::open_csv(RESOURCE_DIR"/Map/FakePrincessThingsMap_0.csv");
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (ThingsMapData[y][x] != "0") {
                int thing_index = std::stoi(ThingsMapData[y][x]);
                BuildThing(0, x, y, thing_index);
                m_FakePrincessThingMap[y][x] = m_CurrentThingMap[0][y][x];
            }
        }
    }

    // 載入RoadMap
    for (int i = 0; i < m_TopFloor; i++) {
        std::vector<std::vector<std::string>> RoadMapData= Read::open_csv(RESOURCE_DIR"/Map/RoadMap_" + std::to_string(i) + ".csv");
        for (int  y= 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                if (RoadMapData[y][x] != "0") {
                    int index = std::stoi(RoadMapData[y][x]);
                    BuildRoad(i, x, y, index);
                }
                else
                    m_CurrentRoadMap[i][y][x] = nullptr;
                m_RoadMap[i][y][x] = m_CurrentRoadMap[i][y][x];
            }
        }
    }

    // 載入ThingsMap
    m_BigEnemies = 0;
    for (int i = 0; i < m_TopFloor; i++) {
        std::vector<std::vector<std::string> > ThingsMapData = Read::open_csv(RESOURCE_DIR"/Map/ThingsMap_" + std::to_string(i) + ".csv");
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                if (ThingsMapData[y][x] != "0") {
                    int index = std::stoi(ThingsMapData[y][x]);
                    BuildThing(i, x, y, index);
                }
                else
                    m_CurrentThingMap[i][y][x] = nullptr;
                m_ThingMap[i][y][x] = m_CurrentThingMap[i][y][x];
            }
        }
        m_StairPosition[0][i] = {-1, -1};
        m_StairPosition[1][i] = {-1, -1};
    }
}

void MapManager::SetScenesManager(const std::shared_ptr<ScenesManager> &scenesManager) {
    m_ScenesManager = scenesManager;
    m_Player->SetSceneManager(scenesManager);
}

// Floor移動
void MapManager::StartTower() {
    ResetTower();
    m_Player->SetVisible(true);
}

void MapManager::EndTower() const{
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (m_CurrentRoadMap[m_CurrentFloor][y][x] != nullptr)
                m_CurrentRoadMap[m_CurrentFloor][y][x]->SetVisible(false);
            if (m_CurrentThingMap[m_CurrentFloor][y][x] != nullptr)
                m_CurrentThingMap[m_CurrentFloor][y][x]->SetVisible(false);
        }
    }
    m_Player->SetVisible(false);
}

void MapManager::ResetTower() {
    m_CurrentFloor = 0;
    m_Player->SetPivot({position_x[5], position_y[10]});
    m_Player->SetPosition(5, 10);
    m_Player->SetVisible(true);
    m_ScenesManager->ResetFloor(m_CurrentFloor);
    for (int i = 0; i < m_TopFloor; i++) {
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                m_CurrentRoadMap[i][y][x] = m_RoadMap[i][y][x];
                m_CurrentThingMap[i][y][x] = m_ThingMap[i][y][x];
                if (m_CurrentRoadMap[i][y][x] != nullptr)
                    m_CurrentRoadMap[i][y][x]->SetVisible(m_CurrentFloor == i);
                if (m_CurrentThingMap[i][y][x] != nullptr)
                    m_CurrentThingMap[i][y][x]->SetVisible(m_CurrentFloor == i);
            }
        }
    }
}

void MapManager::NextFloor() {
    if (m_CurrentFloor >= m_TopFloor - 1)
        return;
    m_StairPosition[0][m_CurrentFloor] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    m_StairPosition[1][m_CurrentFloor + 1] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    MoveFloor(m_CurrentFloor, m_CurrentFloor + 1);
}

void MapManager::PreviousFloor() {
    if (m_CurrentFloor <= 0)
        return;
    m_StairPosition[1][m_CurrentFloor] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    m_StairPosition[0][m_CurrentFloor - 1] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    MoveFloor(m_CurrentFloor, m_CurrentFloor - 1);
}

void MapManager::SpecificFloor(int floornum) {
    if (floornum < 0 || floornum > m_TopFloor || m_CurrentFloor == floornum)
        return;
    if (floornum == 21) {
        m_Player->SetPivot({position_x[5], position_y[10]});
        m_Player->SetPosition(5, 10);
    }
    else if (m_CurrentFloor == 21 && floornum == 17) {
        m_Player->SetPivot({position_x[3], position_y[0]});
        m_Player->SetPosition(3, 0);
    }
    else {
        int x = m_StairPosition[m_CurrentFloor < floornum][floornum].first;
        int y = m_StairPosition[m_CurrentFloor < floornum][floornum].second;
        m_Player->SetPivot({position_x[x], position_y[y]});
        m_Player->SetPosition(x, y);
    }
    MoveFloor(m_CurrentFloor, floornum);
}

void MapManager::FakePrincessStart() {
    m_CurrentRoadMap[m_CurrentFloor][2][5]->SetVisible(false);
    m_CurrentRoadMap[m_CurrentFloor][2][5] = m_Wall;
    m_CurrentRoadMap[m_CurrentFloor][2][5]->SetVisible(true);
}

void MapManager::FakePrincessEnd() {
    m_CurrentRoadMap[m_CurrentFloor][2][5]->SetVisible(false);
    m_CurrentRoadMap[m_CurrentFloor][2][5] = m_RoadMap[m_CurrentFloor][2][5];
    m_CurrentRoadMap[m_CurrentFloor][2][5]->SetVisible(true);
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (m_FakePrincessThingMap[y][x] != nullptr) {
                m_CurrentThingMap[m_CurrentFloor][y][x] = m_FakePrincessThingMap[y][x];
                m_CurrentThingMap[m_CurrentFloor][y][x]->SetVisible(true);
            }
        }
    }
}

void MapManager::MoveFloor(int prefloor ,int nextfloor) {
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            m_CurrentRoadMap[prefloor][y][x]->SetVisible(false);
            m_CurrentRoadMap[nextfloor][y][x]->SetVisible(true);
            if (m_CurrentThingMap[prefloor][y][x] != nullptr) {
                if (!m_CurrentThingMap[prefloor][y][x]->IsVisible()) {
                    m_CurrentThingMap[prefloor][y][x] = nullptr;
                }
                else {
                    m_CurrentThingMap[prefloor][y][x]->SetVisible(false);
                }
            }
            if (m_CurrentThingMap[nextfloor][y][x] != nullptr) {
                m_CurrentThingMap[nextfloor][y][x]->SetVisible(true);
            }
        }
    }
    m_CurrentFloor = nextfloor;

    m_ScenesManager->ResetFloor(m_CurrentFloor);
    m_Fly->SetFloor(m_CurrentFloor);
}

// Player移動
void MapManager::PlayerMoveUp() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    if (y > 0) {
        m_Player->SetForward();
        MovePlayer(x, --y);
    }
}

void MapManager::PlayerMoveDown() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    if (y < 10) {
        m_Player->SetBackward();
        MovePlayer(x, ++y);
    }
}

void MapManager::PlayerMoveLeft() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    if (x > 0) {
        m_Player->SetLeft();
        MovePlayer(--x, y);
    }
}

void MapManager::PlayerMoveRight() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    if (x < 10) {
        m_Player->SetRight();
        MovePlayer(++x, y);
    }
}

void MapManager::MovePlayer(int x, int y) {
    if (m_CurrentThingMap[m_CurrentFloor][y][x] != nullptr) {
        // player 移動
        if (m_CurrentThingMap[m_CurrentFloor][y][x]->IsTraversable() || !m_CurrentThingMap[m_CurrentFloor][y][x]->IsVisible()) {
            m_Player->SetPivot({position_x[x], position_y[y]});
            m_Player->SetPosition(x, y);
        }
        // 物品被碰觸
        if (m_CurrentThingMap[m_CurrentFloor][y][x]->IsVisible()) {
            m_CurrentThingMap[m_CurrentFloor][y][x]->Touched();
        }
    }
    else if (m_CurrentRoadMap[m_CurrentFloor][y][x]->IsTraversable()) {
        // player 移動
        m_Player->SetPivot({position_x[x], position_y[y]});
        m_Player->SetPosition(x, y);
    }
}

[[nodiscard]] bool MapManager::IsDoorOpening() {
    if (m_OpeningDoor == nullptr)
        return false;
    if (m_OpeningDoor->GetCurrentFrameIndex() == 5) {
        m_OpeningDoor->SetPause();
        m_OpeningDoor->SetCurrentFrameIndex(0);
        m_OpeningDoor->SetVisible(false);
        m_OpeningDoor = nullptr;
        return false;
    }
    return true;
}

void MapManager::SetOpeningDoor(Door* door) {
    m_OpeningDoor = door;
}

[[nodiscard]] std::vector<std::vector<std::shared_ptr<Thing>>> MapManager::GetCurrentMap() const {
    std::vector<std::vector<std::shared_ptr<Thing>>> currentMap;
    for (int y = 0; y < 11; y++) {
        std::vector<std::shared_ptr<Thing>> data;
        for (int x = 0; x < 11; x++) {
            data.push_back(m_CurrentThingMap[m_CurrentFloor][y][x]);
        }
        currentMap.push_back(data);
    }
    return currentMap;
}

void MapManager::BuildRoad(int floor, int x, int y, int index) {
    if (std::stoi(m_RoadData[index][3]))
        m_CurrentRoadMap[floor][y][x] = std::make_shared<Road>(m_RoadData[index], true, position_x[x], position_y[y], index);
    else
        m_CurrentRoadMap[floor][y][x] = std::make_shared<Road>(m_RoadData[index], position_x[x], position_y[y], index);
}


void MapManager::BuildThing(int floor, int x, int y, int index) {
    int num = index % 100;
    if (m_CurrentThingMap[floor][y][x] != nullptr)
        if (!m_CurrentThingMap[floor][y][x]->IsVisible())
            m_CurrentThingMap[floor][y][x] = nullptr;
    if (index / 100 == EnemyType)
        m_CurrentThingMap[floor][y][x] = std::make_shared<Enemy>(m_EnemyData[num], position_x[x], position_y[y], index, m_Fighting);
    else if (index / 100 == ItemType)
        m_CurrentThingMap[floor][y][x] = std::make_shared<Item>(m_ItemData[num], position_x[x], position_y[y], index, m_Player, m_ItemDialog);
    else if (index / 100 == NPCType) {
        if (std::stoi(m_NPCData[num][3]))
            m_CurrentThingMap[floor][y][x] = std::make_shared<NPC>(m_NPCData[num], true, floor, position_x[x], position_y[y], index, m_NPCDialog);
        else
            m_CurrentThingMap[floor][y][x] = std::make_shared<NPC>(m_NPCData[num], floor, position_x[x], position_y[y], index, m_NPCDialog);
    }
    else if (index / 100 == DoorType)
        m_CurrentThingMap[floor][y][x] = std::make_shared<Door>(m_DoorData[num], position_x[x], position_y[y], index, m_Player, this);
    else if (index / 100 == StairType)
        m_CurrentThingMap[floor][y][x] = std::make_shared<Stair>(m_StairData[num], position_x[x], position_y[y], index, this);
    else if (index / 100 == ShopType)
        m_CurrentThingMap[floor][y][x] = std::make_shared<Shop>(m_ShopData[num], floor, position_x[x], position_y[y], index, m_ShopDialog);
    else if (index / 100 == BigEnemyType) {
        m_CurrentThingMap[floor][y][x] = std::make_shared<BigEnemy>(m_BigEnemyData[num], position_x[x], position_y[y], m_Fighting);
        m_BigEnemies++;
        if (m_BigEnemies != 8) {
            m_OtherBigEnemies.push_back(m_CurrentThingMap[floor][y][x]);
        }
        if (m_BigEnemies == 9) {
            auto temp = std::dynamic_pointer_cast<BigEnemy>(m_CurrentThingMap[floor][y][x - 1]);
            temp->SetOtherEnemy(m_OtherBigEnemies);
            m_BigEnemies = 0;
            m_OtherBigEnemies.clear();
        }
    }
    else if (index / 100 == FakePrincessType) {
        m_CurrentThingMap[floor][y][x] = std::make_shared<FakePrincess>(m_FakePrincessData[index % 100], m_NPCData[4], floor, position_x[x], position_y[y], m_Fighting, m_NPCDialog, this);
    }
    else {
        LOG_ERROR(std::to_string(index) + " This ThingMap number is incorrect.");
        exit(1);
    }

}