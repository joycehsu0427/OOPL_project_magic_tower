#include <fstream>

#include "ScenesManager.hpp"
#include "Read.hpp"

ScenesManager::ScenesManager(std::shared_ptr<MapManager> &mapmanager, std::shared_ptr<Player> &player) :
m_MapManager(mapmanager), m_Player(player) {
    // m_BackGround 初始化
    m_BackGround = std::make_shared<BackgroundImage>();

    // m_Logging 初始化
    std::vector <std::string> LoggingAnimation;
    for(int i = 1; i <= 4; i++) {
        LoggingAnimation.push_back(RESOURCE_DIR"/bmp/Scene/loading" + std::to_string(i) + ".BMP");
    }
    LoggingAnimation.emplace_back(RESOURCE_DIR"/bmp/Scene/scene1.BMP");
    m_Loading = std::make_shared<AnimationObject>(LoggingAnimation);
    m_Loading->SetVisible(false);

    // m_Story 初始化
    m_Story = std::make_shared<TextObject>(25, Read::open_txt(RESOURCE_DIR"/Text/Story.txt"));
    m_Story->SetPivot({-150, -165});
    m_Story->SetVisible(false);

    // m_Remind 初始化
    m_Remind = std::make_shared<TextObject>(25, "-Press Space-");
    m_Remind->SetPivot({-360, 275});
    m_Remind->SetVisible(false);

    // m_FloorText 初始化
    for (int i = 0; i < 26; i++) {
        if (i == 0)
            m_Floortext.emplace_back("主塔　入口");
        else if (i <= 20)
            m_Floortext.emplace_back("主塔　" + std::to_string(i) + "F");
        else
            m_Floortext.emplace_back("魔塔　" + std::to_string(i-20) + "F");
    }

    // m_Floor 初始化
    m_Floor = std::make_shared<TextObject>(25, m_Floortext[m_MapManager->GetCurrentFloor()]);
    m_Floor->SetPivot({-150, -335});
    m_Floor->SetVisible(false);

    int index_x = 270;
    // m_PlayerStatus 初始化
    m_PlayerStatus = std::make_shared<TextObject>(25, m_Player->GetStatus());
    m_PlayerStatus->SetPivot({index_x, -250});
    m_PlayerStatus->SetVisible(false);

    // m_PlayerLevel 初始化
    m_PlayerLevel = std::make_shared<TextObject>(25, std::to_string(m_Player->GetLevel()));
    m_PlayerLevel->SetPivot({index_x, -207.5});
    m_PlayerLevel->SetVisible(false);

    // m_PlayerHP 初始化
    m_PlayerHP = std::make_shared<TextObject>(25, std::to_string(m_Player->GetHP()));
    m_PlayerHP->SetPivot({index_x, -166});
    m_PlayerHP->SetVisible(false);

    // m_PlayerATK 初始化
    m_PlayerATK = std::make_shared<TextObject>(25, std::to_string(m_Player->GetATK()));
    m_PlayerATK->SetPivot({index_x, -124.5});
    m_PlayerATK->SetVisible(false);

    // m_PlayerDEF 初始化
    m_PlayerDEF = std::make_shared<TextObject>(25, std::to_string(m_Player->GetDEF()));
    m_PlayerDEF->SetPivot({index_x, -83});
    m_PlayerDEF->SetVisible(false);

    // m_PlayerAGI 初始化
    m_PlayerAGI = std::make_shared<TextObject>(25, std::to_string(m_Player->GetAGI()));
    m_PlayerAGI->SetPivot({index_x, -41.5});
    m_PlayerAGI->SetVisible(false);

    // m_PlayerEXP 初始化
    m_PlayerEXP = std::make_shared<TextObject>(25, std::to_string(m_Player->GetEXP()));
    m_PlayerEXP->SetPivot({index_x, 0});
    m_PlayerEXP->SetVisible(false);

    // m_PlayerYellowKey 初始化
    m_PlayerYellowKey = std::make_shared<TextObject>(40, std::to_string(m_Player->GetYellowKey()));
    m_PlayerYellowKey->SetPivot({index_x, 113.5});
    m_PlayerYellowKey->SetVisible(false);

    // m_PlayerBlueKey 初始化
    m_PlayerBlueKey = std::make_shared<TextObject>(40, std::to_string(m_Player->GetBlueKey()));
    m_PlayerBlueKey->SetPivot({index_x, 170.3});
    m_PlayerBlueKey->SetVisible(false);

    // m_PlayerRedKey 初始化
    m_PlayerRedKey = std::make_shared<TextObject>(40, std::to_string(m_Player->GetRedKey()));
    m_PlayerRedKey->SetPivot({index_x, 227});
    m_PlayerRedKey->SetVisible(false);

    // m_PlayerCoins 初始化
    m_PlayerCoins = std::make_shared<TextObject>(40, std::to_string(m_Player->GetCoins()));
    m_PlayerCoins->SetPivot({index_x, 283.8});
    m_PlayerCoins->SetVisible(false);

    m_EndScene = std::make_shared<ImageObject>(RESOURCE_DIR"/bmp/Scene/end.bmp", 50);
    m_EndScene->SetVisible(false);

    m_EndText = std::make_shared<TextObject>(100, "Win!!!", 55);
    m_EndText->SetVisible(false);
}

// ResetText
void ScenesManager::ResetFloor (int courrentfloor) const {
    m_Floor->SetText(m_Floortext[courrentfloor]);
}
void ScenesManager::ResetPlayerStatus()  const {
    m_PlayerStatus->SetText(m_Player->GetStatus());
}

void ScenesManager::ResetPlayerLevel() const {
    m_PlayerLevel->SetText(std::to_string(m_Player->GetLevel()));
}
void ScenesManager::ResetPlayerHP() const {
    m_PlayerHP->SetText(std::to_string(m_Player->GetHP()));
}
void ScenesManager::ResetPlayerATK() const {
    m_PlayerATK->SetText(std::to_string(m_Player->GetATK()));
}
void ScenesManager::ResetPlayerDEF() const {
    m_PlayerDEF->SetText(std::to_string(m_Player->GetDEF()));
}
void ScenesManager::ResetPlayerAGI() const {
    m_PlayerAGI->SetText(std::to_string(m_Player->GetAGI()));
}
void ScenesManager::ResetPlayerEXP() const {
    m_PlayerEXP->SetText(std::to_string(m_Player->GetEXP()));
}
void ScenesManager::ResetPlayerYellowKey() const {
    m_PlayerYellowKey->SetText(std::to_string(m_Player->GetYellowKey()));
}
void ScenesManager::ResetPlayerBlueKey() const {
    m_PlayerBlueKey->SetText(std::to_string(m_Player->GetBlueKey()));
}
void ScenesManager::ResetPlayerRedKey() const {
    m_PlayerRedKey->SetText(std::to_string(m_Player->GetRedKey()));
}
void ScenesManager::ResetPlayerCoins() const {
    m_PlayerCoins->SetText(std::to_string(m_Player->GetCoins()));
}

void ScenesManager::NextScene() {
    if (m_scene >= 7) {
        m_BackGround->SetVisible(false);
        return;
    }
    m_BackGround->NextScene(++m_scene);
}

void ScenesManager::EndScene(const bool is_win) {
    m_EndScene->SetVisible(true);
    m_EndText->SetVisible(true);
    if (is_win) {
        m_EndText->SetText("Win!!!");
    }
    else {
        m_EndText->SetText("Game Over!");
    }
}
