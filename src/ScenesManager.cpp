#include "ScenesManager.hpp"
#include "BackgroundImage.hpp"

ScenesManager::ScenesManager() {
    m_BackGround = std::make_shared<BackgroundImage>();
}

void ScenesManager::NextScene() {
    if (m_scene >= 3) {
        m_BackGround->SetVisible(false);
        return;
    }
    m_BackGround->NextScene(m_scene++);
};