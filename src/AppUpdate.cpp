#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Update() {

    //TODO: do your things here and delete this line <3

    // START
    if (m_Scene == Scene::START) {
        // 按下 Space 切換到故事
        if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
            LOG_DEBUG("Go to Story");
            m_Scene = Scene::STORY;
            m_SceneManager->NextScene();


            m_SceneManager->GetLogging()->SetVisible(true);
            m_SceneManager->GetLogging()->SetLooping(true);
            m_SceneManager->GetLogging()->SetPlaying();
        }
    }

    // STORY
    if (m_Scene == Scene::STORY) {
        // std::shared_ptr<Loaing>
        if (m_SceneManager->GetLogging()->IsLooping() && m_SceneManager->GetLogging()->IsPlaying()) {
            if (m_SceneManager->GetLogging()->GetCurrentFrameIndex() == 4) {
                m_SceneManager->GetLogging()->SetVisible(false);
                m_SceneManager->GetLogging()->SetLooping(false);
                m_SceneManager->GetLogging()->SetPause();
                m_SceneManager->StartStory();
            }
        }
        else {
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                LOG_DEBUG("Go to Tower");
                m_Scene = Scene::TOWER;
                m_SceneManager->EndStory();
                m_MapManager->StartTower();
            }
        }
    }
    // TOWER
    if (m_Scene == Scene::TOWER) {
        if (Util::Input::IsKeyUp(Util::Keycode::UP)) {
            m_MapManager->PlayerMoveUp();
        }
        if (Util::Input::IsKeyUp(Util::Keycode::DOWN)) {
            m_MapManager->PlayerMoveDown();
        }
        if (Util::Input::IsKeyUp(Util::Keycode::LEFT)) {
            m_MapManager->PlayerMoveLeft();
        }
        if (Util::Input::IsKeyUp(Util::Keycode::RIGHT)) {
            m_MapManager->PlayerMoveRight();
        }
    }
    //DEAD

    //WIN


    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Renderer.Update();
}
