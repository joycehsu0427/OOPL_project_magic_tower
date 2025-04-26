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
#include "ScenesManager.hpp"
#include "Read.hpp"

#include "Util/Logger.hpp"

MapManager::MapManager(const std::shared_ptr<Fighting> &fighting, const std::shared_ptr<ItemDialog> &itemDialog,
    const std::shared_ptr<NPCDialog> &npcDialog, const std::shared_ptr<ShopDialog> &shopDialog,
    const std::shared_ptr<Fly> &fly) : m_Fly(fly) {
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
    m_RoadData = Read::open_csv(RESOURCE_DIR"/Data/Road.csv");

    // 載入RoadMap
    for (int i = 0; i < m_TopFloor; i++) {
        std::vector<std::vector<std::string>> RoadMapData= Read::open_csv(RESOURCE_DIR"/Map/RoadMap_" + std::to_string(i) + ".csv");
        for (int  y= 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                int index = std::stoi(RoadMapData[y][x]);
                m_RoadMap[i][y][x] = std::make_shared<Road>(m_RoadData[index], position_x[x], position_y[y], index);
            }
        }
    }

    // 載入ThingsMap
    for (int i = 0; i < m_TopFloor; i++) {
        std::vector<std::vector<std::string> > ThingsMapData = Read::open_csv(RESOURCE_DIR"/Map/ThingsMap_" + std::to_string(i) + ".csv");
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                if (ThingsMapData[y][x] != "0") {
                    int index = std::stoi(ThingsMapData[y][x]);
                    int num = index % 100;
                    if (index / 100 == EnemyType)
                        m_ThingMap[i][y][x] = std::make_shared<Enemy>(m_EnemyData[num], position_x[x], position_y[y], index, fighting);
                    else if (index / 100 == ItemType)
                        m_ThingMap[i][y][x] = std::make_shared<Item>(m_ItemData[num], position_x[x], position_y[y], index, m_Player, itemDialog);
                    else if (index / 100 == NPCType)
                        m_ThingMap[i][y][x] = std::make_shared<NPC>(m_NPCData[num], i, position_x[x], position_y[y], index, npcDialog);
                    else if (index / 100 == DoorType)
                        m_ThingMap[i][y][x] = std::make_shared<Door>(m_DoorData[num], position_x[x], position_y[y], index, m_Player);
                    else if (index / 100 == StairType)
                        m_ThingMap[i][y][x] = std::make_shared<Stair>(m_StairData[num], position_x[x], position_y[y], index, this);
                    else if (index / 100 == ShopType)
                        m_ThingMap[i][y][x] = std::make_shared<Shop>(m_ShopData[num], i, position_x[x], position_y[y], index, shopDialog);
                    else {
                        LOG_ERROR("This number is incorrect.");
                        exit(1);
                    }
                }
            }
        }
        m_StairPosition[0][i] = {-1, -1};
        m_StairPosition[1][i] = {-1, -1};
        // LOG_DEBUG("UP" + std::to_string(m_StairPosition[0][i].first) + "," + std::to_string(m_StairPosition[0][i].second));
        // LOG_DEBUG("DOWN" + std::to_string(m_StairPosition[1][i].first) + "," + std::to_string(m_StairPosition[1][i].second));
    }

}

void MapManager::SetScenesManager(std::shared_ptr<ScenesManager> &scenesManager) {
    m_ScenesManager = scenesManager;
    m_Player->SetSceneManager(scenesManager);
}


// Floor移動
void MapManager::StartTower() {
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
void MapManager::EndTower() const{
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            m_RoadMap[m_CurrentFloor][y][x]->SetVisible(false);
            m_ThingMap[m_CurrentFloor][y][x]->SetVisible(false);
        }
    }
    m_Player->SetVisible(false);
}

void MapManager::NextFloor() {
    if (m_CurrentFloor >= m_TopFloor - 1)
        return;
    m_StairPosition[0][m_CurrentFloor] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    m_StairPosition[1][m_CurrentFloor + 1] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    // LOG_DEBUG("UP" + std::to_string(m_CurrentFloor) + ":" + std::to_string(m_StairPosition[0][m_CurrentFloor].first) + "," + std::to_string(m_StairPosition[0][m_CurrentFloor].second));
    MoveFloor(m_CurrentFloor, m_CurrentFloor + 1);
}

void MapManager::PreviousFloor() {
    if (m_CurrentFloor <= 0)
        return;
    m_StairPosition[1][m_CurrentFloor] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    m_StairPosition[0][m_CurrentFloor - 1] = {m_Player->GetPositionX(), m_Player->GetPositionY()};
    // LOG_DEBUG("DOWN" + std::to_string(m_CurrentFloor) + ":" + std::to_string(m_StairPosition[1][m_CurrentFloor].first) + "," + std::to_string(m_StairPosition[1][m_CurrentFloor].second));
    MoveFloor(m_CurrentFloor, m_CurrentFloor - 1);
}

void MapManager::SpecificFloor(int floornum) {
    if (floornum < 0 || floornum > m_TopFloor || m_CurrentFloor == floornum)
        return;
    int x = m_StairPosition[m_CurrentFloor < floornum][floornum].first;
    int y = m_StairPosition[m_CurrentFloor < floornum][floornum].second;
    // LOG_DEBUG(std::to_string(m_CurrentFloor < floornum) + "--" + std::to_string(x) + "," + std::to_string(y));
    m_Player->SetPivot({position_x[x], position_y[y]});
    m_Player->SetPosition(x, y);
    MoveFloor(m_CurrentFloor, floornum);
}

void MapManager::MoveFloor(int prefloor ,int nextfloor) {
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            m_RoadMap[prefloor][y][x]->SetVisible(false);
            m_RoadMap[nextfloor][y][x]->SetVisible(true);
            if (m_ThingMap[prefloor][y][x] != nullptr) {
                if (!m_ThingMap[prefloor][y][x]->IsVisible()) {
                    m_ThingMap[prefloor][y][x] = nullptr;
                }
                else {
                    m_ThingMap[prefloor][y][x]->SetVisible(false);
                }
            }
            if (m_ThingMap[nextfloor][y][x] != nullptr) {
                m_ThingMap[nextfloor][y][x]->SetVisible(true);
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
        MovePlayer(x, --y);
    }
}

void MapManager::PlayerMoveDown() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    if (y < 10) {
        MovePlayer(x, ++y);
    }
}

void MapManager::PlayerMoveLeft() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    if (x > 0) {
        MovePlayer(--x, y);
    }
}

void MapManager::PlayerMoveRight() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    if (x < 10) {
        MovePlayer(++x, y);
    }
}

void MapManager::MovePlayer(int x, int y) {
    if (m_ThingMap[m_CurrentFloor][y][x] != nullptr) {
        // player 移動
        if (m_ThingMap[m_CurrentFloor][y][x]->IsTraversable() || !m_ThingMap[m_CurrentFloor][y][x]->IsVisible()) {
            m_Player->SetPivot({position_x[x], position_y[y]});
            m_Player->SetPosition(x, y);
        }
        // 物品被碰觸
        if (m_ThingMap[m_CurrentFloor][y][x]->IsVisible()) {
            m_ThingMap[m_CurrentFloor][y][x]->Touched();
        }
    }
    else if (m_RoadMap[m_CurrentFloor][y][x]->IsTraversable()) {
        // player 移動
        m_Player->SetPivot({position_x[x], position_y[y]});
        m_Player->SetPosition(x, y);
    }
}

[[nodiscard]] std::vector<std::vector<std::shared_ptr<Thing>>> MapManager::GetCurrentMap() const {
    std::vector<std::vector<std::shared_ptr<Thing>>> currentMap;
    for (int y = 0; y < 11; y++) {
        std::vector<std::shared_ptr<Thing>> data;
        for (int x = 0; x < 11; x++) {
            data.push_back(m_ThingMap[m_CurrentFloor][y][x]);
        }
        currentMap.push_back(data);
    }
    return currentMap;
}

