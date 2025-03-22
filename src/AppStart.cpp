#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_SceneManager = std::make_shared<ScenesManager>();
    m_Renderer.AddChildren(m_SceneManager->GetChildren());

    // m_Text = std::make_shared<TextObject>(25, "主塔　入口");
    // m_Text->SetPivot({-150, -335});
    // m_Renderer.AddChild(m_Text);

    m_MapManager = std::make_shared<MapManager>();
    m_Renderer.AddChildren(m_MapManager->GetChildren());
    m_Player = m_MapManager->GetPlayer();





    // m_Player = std::make_shared<Player>();
    // m_Renderer.AddChild(m_Player);
    // m_Player->SetVisible(true);
    // m_Player->SetPivot({38.5f, -462});
    // m_Enemy = std::make_shared<Enemy>("green_slime","綠色史萊母",40,18,1,0,
    //     1,1,0,0,1,0,"0",0);
    // m_Enemy->SetVisible(false);
    // m_Renderer.AddChild(m_Enemy);
    //
    // m_Item = std::make_shared<Item>("yellow_key",0,0,0,0,0,0,0,
    // 1,0,0,0,0);
    // m_Item->SetVisible(true);
    // m_Renderer.AddChild(m_Item);

    // std::vector<std::string> data = {"wall", "wall","0", "0"};
    // m_Road = std::make_shared<Road>(data, 0, 0);
    // m_Road->SetVisible(true);
    // m_Renderer.AddChild(m_Road);

    m_CurrentState = State::UPDATE;

}
