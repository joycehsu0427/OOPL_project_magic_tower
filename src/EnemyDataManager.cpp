#include "EnemyDataManager.hpp"
#include "Read.hpp"
#include "Util/Logger.hpp"

EnemyDataManager::EnemyDataManager() {
    float scale = 0.732f;
    m_BackGround = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/Black.bmp", 30);
    m_BackGround->SetPivot({-194, 0});
    m_BackGround->SetVisible(false);
    m_BackGround->SetScale(scale);
    m_Children.push_back(m_BackGround);

    for (int i = 0; i < 3; i++)
        m_EnemyData[i] = std::make_shared<EnemyData>(i);

    float arrow_y = 320;
    m_LeftArrow = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/left_arrow_gray.png", 35);
    m_LeftArrow->SetPivot({-490, arrow_y});
    m_LeftArrow->SetVisible(false);
    m_LeftArrow->SetScale(scale);
    m_Children.push_back(m_LeftArrow);

    m_RightArrow = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Special/right_arrow_gray.png", 35);
    m_RightArrow->SetPivot({-580, arrow_y});
    m_RightArrow->SetVisible(false);
    m_RightArrow->SetScale(scale);
    m_Children.push_back(m_RightArrow);

    m_RemindText = std::make_shared<TextObject>(25, "-Space-", 35);
    m_RemindText->SetPivot({-402, 275});
    m_RemindText->SetVisible(false);
    m_Children.push_back(m_RemindText);

}
void EnemyDataManager::NextPage() {
    if (m_CurrentPage != m_Page - 1) {
        if (m_CurrentPage == 0)
            m_LeftArrow->SetImage(RESOURCE_DIR"/bmp/Special/left_arrow_white.png");
        m_CurrentPage++;
        if (m_CurrentPage == m_Page - 1)
            m_RightArrow->SetImage(RESOURCE_DIR"/bmp/Special/right_arrow_gray.png");
        SetEnemies();
    }
}

void EnemyDataManager::PrePage() {
    if (m_CurrentPage != 0) {
        if (m_CurrentPage == m_Page - 1)
            m_RightArrow->SetImage(RESOURCE_DIR"/bmp/Special/right_arrow_white.png");
        m_CurrentPage--;
        if (m_CurrentPage == 0)
            m_LeftArrow->SetImage(RESOURCE_DIR"/bmp/Special/left_arrow_gray.png");
        SetEnemies();
    }
}


void EnemyDataManager::SetPlayer(const std::shared_ptr<Player> &player) const {
    for (auto &enemydata : m_EnemyData)
        enemydata->SetPlayer(player);
}

void EnemyDataManager::SetEnemyDataManager(const std::vector<std::vector<std::shared_ptr<Thing>>> &currentMap) {
    SetVisible(true);
    std::shared_ptr<Enemy> m_Enemy[28] = {nullptr};
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (currentMap[y][x] != nullptr) {
                if (currentMap[y][x]->IsVisible()) {
                    int index = currentMap[y][x]->GetIndex();
                    if (index / 100 == 1) {
                        if (m_Enemy[index % 100] == nullptr) {
                            auto temp = std::dynamic_pointer_cast<Enemy>(currentMap[y][x]);
                            m_Enemy[index % 100] = temp;
                        }
                    }
                }
            }
        }
    }
    m_Enemy_List.clear();
    for (int i = 1; i < 28; i++) {
        if (m_Enemy[i] != nullptr)
            m_Enemy_List.push_back(m_Enemy[i]);
    }

    m_CurrentPage = 0;
    if (!m_Enemy_List.empty()) {
        m_Page = (m_Enemy_List.size() - 1) / 3 + 1;
        SetEnemies();
    }
    else {
        m_Page = 1;
        for (auto &enemydata : m_EnemyData)
            enemydata->SetVisible(false);
    }

    m_LeftArrow->SetImage(RESOURCE_DIR"/bmp/Special/left_arrow_gray.png");
    if (m_Page > 1)
        m_RightArrow->SetImage(RESOURCE_DIR"/bmp/Special/right_arrow_white.png");
    else
        m_RightArrow->SetImage(RESOURCE_DIR"/bmp/Special/right_arrow_gray.png");

}

void EnemyDataManager::SetEnemies() const {
    long long unsigned int num = m_CurrentPage * 3;
    for (auto &enemydata : m_EnemyData)
        enemydata->SetVisible(true);
    if (m_Enemy_List.size() >= num + 3) {
        // LOG_DEBUG(std::to_string(m_EnemyList[num]) + ", " + std::to_string(m_EnemyList[num+1]) + ", " + std::to_string(m_EnemyList[num+2]));
        m_EnemyData[0]->SetEnemy(m_Enemy_List[num]);
        m_EnemyData[1]->SetEnemy(m_Enemy_List[num + 1]);
        m_EnemyData[2]->SetEnemy(m_Enemy_List[num + 2]);
    }
    else if (m_Enemy_List.size() == num + 2) {
        // LOG_DEBUG(std::to_string(m_EnemyList[num]) + ", " + std::to_string(m_EnemyList[num+1]));
        m_EnemyData[0]->SetEnemy(m_Enemy_List[num]);
        m_EnemyData[1]->SetEnemy(m_Enemy_List[num + 1]);
        m_EnemyData[2]->SetVisible(false);
    }
    else if (m_Enemy_List.size() == num + 1) {
        // LOG_DEBUG(std::to_string(m_EnemyList[num]));
        m_EnemyData[0]->SetEnemy(m_Enemy_List[num]);
        m_EnemyData[1]->SetVisible(false);
        m_EnemyData[2]->SetVisible(false);
    }
}

