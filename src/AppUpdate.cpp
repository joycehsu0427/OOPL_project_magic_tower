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
    else if (m_Scene == Scene::STORY) {
        std::shared_ptr<AnimationObject> loading = m_SceneManager->GetLoading();
        if (loading->IsLooping() && loading->IsPlaying()) {
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
    else if (m_Scene == Scene::TOWER) {
        if (m_TowerState == TowerState::MOVING) {
            if (Util::Input::IsKeyUp(Util::Keycode::UP)) {
                m_MapManager->PlayerMoveUp();
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::DOWN)) {
                m_MapManager->PlayerMoveDown();
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::LEFT)) {
                m_MapManager->PlayerMoveLeft();
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::RIGHT)) {
                m_MapManager->PlayerMoveRight();
            }
            if (m_ItemDialog->IsVisible())
                m_TowerState = TowerState::ITEMDIALOG;
            else if (m_NPCDialog->IsVisible())
                m_TowerState = TowerState::NPCDIALOG;
            else if (m_Fighting->IsVisible()) {
                m_TowerState = TowerState::ENEMYFIGHTING;
                m_FightingTimer = 0;
            }
            else if (m_ShopDialog->IsVisible())
                m_TowerState = TowerState::SHOPDIALOG;
        }
        else if (m_TowerState == TowerState::ITEMDIALOG) {
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                m_ItemDialog->SetVisible(false);
                m_TowerState = TowerState::MOVING;
            }
        }
        else if (m_TowerState == TowerState::NPCDIALOG) {
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                m_NPCDialog->NextDialog();
                m_TowerState = TowerState::MOVING;
            }
        }
        else if (m_TowerState == TowerState::ENEMYFIGHTING) {
            if (m_Fighting->IsFighting()) {
                // 打鬥過程
                m_FightingTimer++;
                int timer = 20;
                if (m_FightingTimer % timer == 0) {
                    if (m_Fighting->IsEnd()) {
                        m_Fighting->EndFighting();
                        if (m_Player->GetHP()<=0) {
                            m_Scene = Scene::DEAD;
                            LOG_DEBUG("Dead");
                        }
                    }
                    else if (m_FightingTimer == timer) {
                        m_Fighting->PlayerATK();
                    }
                    else {
                        m_Fighting->EnemyATK();
                        m_FightingTimer = 0;
                    }
                }
                if (Util::Input::IsKeyUp(Util::Keycode::Q)) {
                    m_Fighting->QuitFighting();
                    m_TowerState = TowerState::MOVING;
                }
            }
            else {
                if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                    m_Fighting->SetVisible(false);
                    m_TowerState = TowerState::MOVING;
                }
            }
        }
        else if (m_TowerState == TowerState::SHOPDIALOG) {
            if (Util::Input::IsKeyUp(Util::Keycode::UP)) {
                m_ShopDialog->OptionUp();
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::DOWN)) {
                m_ShopDialog->OptionDown();
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                m_ShopDialog->SetVisible(false);
            }
            else if (m_ShopDialog->IsVisible()) {
                m_TowerState = TowerState::MOVING;
            }
        }
    }
    //DEAD
    else if (m_Scene == Scene::DEAD) {
        m_SceneManager->EndScene(false);
    }

    //WIN
    else if (m_Scene == Scene::WIN) {
        m_SceneManager->EndScene(true);
    }


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
