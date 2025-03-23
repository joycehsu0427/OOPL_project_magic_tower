#include "App.hpp"

#include "AnimationObject.hpp"

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

            std::shared_ptr<AnimationObject> loading = m_SceneManager->GetLoading();
            loading->SetVisible(true);
            loading->SetLooping(true);
            loading->SetPlaying();
        }
    }

    // STORY
    if (m_Scene == Scene::STORY) {
        std::shared_ptr<AnimationObject> loading = m_SceneManager->GetLoading();
        if (m_SceneManager->GetLoading()->IsLooping() && m_SceneManager->GetLoading()->IsPlaying()) {
            if (loading->GetCurrentFrameIndex() == 4) {
                loading->SetVisible(false);
                loading->SetLooping(false);
                loading->SetPause();
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
