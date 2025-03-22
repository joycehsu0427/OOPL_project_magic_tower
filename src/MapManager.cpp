#include <fstream>
#include <sstream>

#include "MapManager.hpp"

#include "Enemy.hpp"
#include "Item.hpp"
#include "NPC.hpp"
#include "Door.hpp"
#include "Stair.hpp"
#include "Shop.hpp"

#include "Util/Logger.hpp"

MapManager::MapManager() {
    // xy軸位置設置
    for (int i = 0; i < 11; i++) {
        position_x[i] = start_position_x - i * 77;
        position_y[i] = start_position_y + i * 77;
    }

    // 載入Enemy基本資料
    m_EnemyData = open_csv(RESOURCE_DIR"/Data/Enemy.csv");

    // 載入Item基本資料
    m_ItemData = open_csv(RESOURCE_DIR"/Data/Item.csv");

    // 載入NPC基本資料
    m_NPCData = open_csv(RESOURCE_DIR"/Data/NPC.csv");

    // 載入Door基本資料
    m_DoorData = open_csv(RESOURCE_DIR"/Data/Door.csv");

    // 載入Stair基本資料
    m_StairData = open_csv(RESOURCE_DIR"/Data/Stair.csv");

    // 載入Shop基本資料
    m_ShopData = open_csv(RESOURCE_DIR"/Data/Shop.csv");

    // 載入Road基本資料
    m_RoadData = open_csv(RESOURCE_DIR"/Data/Road.csv");

    // 載入RoadMap
    for (int i = 0; i < 1; i++) {
        std::vector<std::vector<std::string>> RoadMapData= open_csv(RESOURCE_DIR"/Map/RoadMap_" + std::to_string(i) + ".csv");
        for (int  y= 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                int index = std::stoi(RoadMapData[y][x]);
                m_RoadMap[i][y][x] = std::make_shared<Road>(m_RoadData[index], position_x[x], position_y[y]);
                m_RoadMap[i][y][x]->SetVisible(false);
            }
        }
    }

    // 載入ThingsMap
    for (int i = 0; i < 1; i++) {
        std::vector<std::vector<std::string> > ThingsMapData = open_csv(RESOURCE_DIR"/Map/ThingsMap_" + std::to_string(i) + ".csv");
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                if (ThingsMapData[y][x] != "0") {
                    LOG_DEBUG(ThingsMapData[y][x]);
                    int index = std::stoi(ThingsMapData[y][x]);
                    int num = index % 100;
                    if (index / 100 == 1)
                        m_ThingMap[i][y][x] = std::make_shared<Enemy>(m_EnemyData[num], position_x[x], position_y[y]);
                    else if (index / 100 == 2)
                        m_ThingMap[i][y][x] = std::make_shared<Item>(m_ItemData[num], position_x[x], position_y[y]);
                    else if (index / 100 == 3)
                        m_ThingMap[i][y][x] = std::make_shared<NPC>(m_NPCData[num], i, position_x[x], position_y[y]);
                    else if (index / 100 == 4)
                        m_ThingMap[i][y][x] = std::make_shared<Door>(m_DoorData[num], position_x[x], position_y[y]);
                    else if (index / 100 == 5)
                        m_ThingMap[i][y][x] = std::make_shared<Stair>(m_StairData[num], position_x[x], position_y[y]);
                    else
                        m_ThingMap[i][y][x] = std::make_shared<Shop>(m_ShopData[num], position_x[x], position_y[y]);

                    m_ThingMap[i][y][x]->SetVisible(false);
                }
            }
        }
    }


    //m_Player 初始化
    m_Player = std::make_shared<Player> (position_x[5], position_y [10], 5, 10);
    m_Player->SetZIndex(10);
    m_Player->SetVisible(false);
}

// Player移動
void MapManager::PlayerMoveUp() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    // LOG_DEBUG("DOWN" + std::to_string(x) + "," + std::to_string(y));
    if (y > 0) {
        move(x, --y);
    }
}

void MapManager::PlayerMoveDown() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    // LOG_DEBUG("UP" + std::to_string(x) + "," + std::to_string(y));
    if (y < 10) {
        move(x, ++y);
    }
}

void MapManager::PlayerMoveLeft() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    // LOG_DEBUG("LEFT" + std::to_string(x) + "," + std::to_string(y));
    if (x > 0) {
        move(--x, y);
    }
}

void MapManager::PlayerMoveRight() {
    int x = m_Player->GetPositionX();
    int y = m_Player->GetPositionY();
    // LOG_DEBUG("RIGHT" + std::to_string(x) + "," + std::to_string(y));
    if (x < 10) {
        move(++x, y);
    }
}

void MapManager::move(int x, int y) {
    if (m_ThingMap[m_CurrentFloor][y][x] != nullptr) {
        m_ThingMap[m_CurrentFloor][y][x]->Touched();
        if (m_ThingMap[m_CurrentFloor][y][x]->IsTraversable()) {
            m_Player->SetPivot({position_x[x], position_y[y]});
            m_Player->SetPosition(x, y);
        }

    }
    if (m_ThingMap[m_CurrentFloor][y][x] == nullptr && m_RoadMap[m_CurrentFloor][y][x]->IsTraversable()) {
        m_Player->SetPivot({position_x[x], position_y[y]});
        m_Player->SetPosition(x, y);
    }
}


// 讀取資料
std::vector<std::vector<std::string>> MapManager::open_csv(std::string filepath) {
    std::vector<std::vector<std::string>> data;
    std::ifstream inFile(filepath, std::ios::in);
    if (!inFile) {
        exit(1);
    }
    std::string line;
    while (getline(inFile, line)) {
        data.push_back(split_csv(line));
    }
    inFile.close();
    return data;
}

std::vector<std::string> MapManager::split_csv(std::string line) {
    std::vector<std::string> arr;
    std::istringstream delim(line);
    std::string token;
    int c = 0;
    while (getline(delim, token, ','))
    {
        arr.push_back(token);
        c++;
    }
    return  arr;
}
