#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "ScenesManager.hpp"

void App::Start() {
    LOG_TRACE("Start");


    m_Scene = std::make_shared<ScenesManager>();
    m_Renderer.AddChild(m_Scene->GetBackGround());

    m_CurrentState = State::UPDATE;

}
