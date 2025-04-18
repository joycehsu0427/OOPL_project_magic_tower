#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    // 設置ItemDialog
    m_ItemDialog = std::make_shared<ItemDialog>();
    m_Renderer.AddChildren(m_ItemDialog->GetChildren());

    // 設置NPCDialog
    m_NPCDialog = std::make_shared<NPCDialog>(m_ItemDialog);
    m_Renderer.AddChildren(m_NPCDialog->GetChildren());

    //設置ShopDialog
    m_ShopDialog = std::make_shared<ShopDialog>();
    m_Renderer.AddChildren(m_ShopDialog->GetChildren());
    // m_ShopDialog->SetVisible(true);

    // 設置Fighting
    m_Fighting = std::make_shared<Fighting>();
    m_Renderer.AddChildren(m_Fighting->GetChildren());

    // 設置MapManager
    m_MapManager = std::make_shared<MapManager>(m_Fighting, m_ItemDialog, m_NPCDialog, m_ShopDialog);
    m_Renderer.AddChildren(m_MapManager->GetChildren());

    // 設置Player
    m_Player = m_MapManager->GetPlayer();

    // 設定Fighting的Player指標
    m_Fighting->SetPlayer(m_Player);

    // 設定NPCDialog的Player指標
    m_NPCDialog->SetPlayer(m_Player);

    // 設定ShopDialog的Player指標
    m_ShopDialog->SetPlayer(m_Player);

    // 設置SceneManager
    m_SceneManager = std::make_shared<ScenesManager>(m_MapManager, m_Player);
    m_Renderer.AddChildren(m_SceneManager->GetChildren());

    // 設定MapManager的SceneManager指標
    m_MapManager->SetScenesManager(m_SceneManager);

    m_CurrentState = State::UPDATE;

}
