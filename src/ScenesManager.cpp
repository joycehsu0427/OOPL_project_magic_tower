#include <fstream>

#include "ScenesManager.hpp"

ScenesManager::ScenesManager() {
    //m_BackGround 初始化
    m_BackGround = std::make_shared<BackgroundImage>();

    //m_Logging 初始化
    std::vector <std::string> LoggingAnimation;
    for(int i = 1; i <= 4; i++) {
        LoggingAnimation.push_back(RESOURCE_DIR"/bmp/Scene/logging" + std::to_string(i) + ".BMP");
    }
    LoggingAnimation.push_back(RESOURCE_DIR"/bmp/Scene/scene1.BMP");
    m_Logging = std::make_shared<AnimationObject>(LoggingAnimation);
    m_Logging->SetVisible(false);

    // 讀取Story.txt
    std::string str = "";
    std::ifstream inFile(RESOURCE_DIR"/Text/Story.txt", std::ios::in);
    std::string s;
    while (std::getline(inFile, s)) {
        str += s + "\n";
    }
    inFile.close();

    //m_Story 初始化
    m_Story = std::make_shared<TextObject>(25, str);
    m_Story->SetPivot({-150, -165});
    m_Story->SetVisible(false);

    //m_Remind 初始化
    m_Remind = std::make_shared<TextObject>(25, "-Press Space-");
    m_Remind->SetPivot({-360, 275});
    m_Remind->SetVisible(false);

    //m_Title 初始化
    m_Title = std::make_shared<TextObject>(25, "主塔　入口");
    m_Title->SetPivot({-150, -335});
    m_Title->SetVisible(false);

}

void ScenesManager::NextScene() {
    if (m_scene >= 7) {
        m_BackGround->SetVisible(false);
        return;
    }
    m_BackGround->NextScene(++m_scene);
}
