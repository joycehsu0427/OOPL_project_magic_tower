#include "App.hpp"

#include "AnimationObject.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Update() {
    // START
    if (m_Scene == Scene::START) {
        // 按下 Space 切換到故事
        if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
            LOG_DEBUG("Go to Story");
            m_Scene = Scene::STORY;
            m_SceneManager->NextScene();

            std::shared_ptr<AnimationObject> loading = m_SceneManager->GetLoading();
            loading->SetVisible(true);
            loading->SetPlaying();
        }
    }

    // STORY
    else if (m_Scene == Scene::STORY) {
        std::shared_ptr<AnimationObject> loading = m_SceneManager->GetLoading();
        if (loading->IsLooping() && loading->IsPlaying()) {
            if (loading->GetCurrentFrameIndex() == 4) {
                loading->SetVisible(false);
                loading->SetPause();
                m_SceneManager->StartStory();
            }
        }
        else {
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                LOG_DEBUG("Go to Tower");
                m_Scene = Scene::TOWER;
                m_TowerState = TowerState::MOVING;
                m_SceneManager->EndStory();
                m_MapManager->StartTower();
                m_ShopDialog->ResetShopDialog();
                m_Fly->ResetFly();
            }
        }
    }

    // TOWER
    else if (m_Scene == Scene::TOWER) {
        if (m_TowerState == TowerState::MOVING) {
            if (m_Player->GetWin()) {
                m_MapManager->EndTower();
                m_SceneManager->EndScene(true);
                m_Scene = Scene::END;
                LOG_DEBUG("Win");
            }
            if (!m_MapManager->IsDoorOpening()) {
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
                else if (Util::Input::IsKeyUp(Util::Keycode::D) && m_Player->CanSeeEnemyData()) {
                    m_EnemyDataManager->SetEnemyDataManager(m_MapManager->GetCurrentMap());
                    m_TowerState = TowerState::EnemyData;
                }
                else if (Util::Input::IsKeyUp(Util::Keycode::F) && m_Player->CanFly() && m_MapManager->GetCurrentFloor() <= 20) {
                    m_Fly->StartFly();
                    m_TowerState = TowerState::FLYING;
                }
                else if (Util::Input::IsKeyUp(Util::Keycode::R)) {
                    m_MapManager->ResetTower();
                    m_MapManager->EndTower();
                    m_SceneManager->StartScene();
                    m_Player->ResetData();
                    m_Scene = Scene::START;
                }
                else if (Util::Input::IsKeyUp(Util::Keycode::W)) {
                    m_NoticeImage->SetVisible(true);
                    m_TowerState = TowerState::Notice;
                }
                else if (Util::Input::IsKeyUp(Util::Keycode::A)) {
                    m_Player->SetCheating(!m_Player->GetCheating());
                }
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
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE) ||
                Util::Input::IsKeyUp(Util::Keycode::UP) ||
                Util::Input::IsKeyUp(Util::Keycode::DOWN) ||
                Util::Input::IsKeyUp(Util::Keycode::LEFT) ||
                Util::Input::IsKeyUp(Util::Keycode::RIGHT)) {
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
                int timer = 25;
                if (Util::Input::IsKeyUp(Util::Keycode::S)) {
                    if (m_FightingSpeedUp) {
                        m_FightingTimer *= 5;
                        m_FightingSpeedUp = false;
                    }
                    else {
                        m_FightingTimer /= 5;
                        m_FightingSpeedUp = true;
                    }
                }
                if (m_FightingSpeedUp) {
                    timer /= 5;
                }
                if (m_FightingTimer % timer == 0) {
                    if (m_Fighting->IsEnd()) {
                        m_Fighting->EndFighting();
                        if (m_Player->GetHP()<=0) {
                            m_Scene = Scene::END;
                            m_Fighting->SetVisible(false);
                            m_MapManager->EndTower();
                            m_SceneManager->EndScene(false);
                            LOG_DEBUG("Dead");
                        }
                    }
                    else if (m_FightingTimer == timer) {
                        m_Fighting->PlayerATK();
                    }
                    else {
                        m_Fighting->EnemyATK();
                        if (m_Fighting->IsEnemyATKEnd())
                            m_FightingTimer = 0;
                    }
                }
                else if (m_FightingTimer % timer == timer / 2 + timer / 4) {
                    if (m_Player->GetHP()>0) {
                        m_Fighting->ClearEffect();
                    }
                    else {
                        LOG_DEBUG("Player dead");
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
                m_ShopDialog->Fixed();
            }
            else if (!m_ShopDialog->IsVisible()) {
                m_TowerState = TowerState::MOVING;
            }
        }
        else if (m_TowerState == TowerState::EnemyData) {
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                m_EnemyDataManager->SetVisible(false);
                m_TowerState = TowerState::MOVING;
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::LEFT)) {
                m_EnemyDataManager->PrePage();
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::RIGHT)) {
                m_EnemyDataManager->NextPage();
            }
        }
        else if (m_TowerState == TowerState::FLYING) {
            if (Util::Input::IsKeyUp(Util::Keycode::UP))
                m_Fly->Up();
            else if (Util::Input::IsKeyUp(Util::Keycode::DOWN))
                m_Fly->Down();
            else if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                m_Fly->Confirm();
                m_TowerState = TowerState::MOVING;
            }
            else if (Util::Input::IsKeyUp(Util::Keycode::F)) {
                m_Fly->SetVisible(false);
                m_TowerState = TowerState::MOVING;
            }
        }
        else if (m_TowerState == TowerState::Notice) {
            if (Util::Input::IsKeyUp(Util::Keycode::W)) {
                m_NoticeImage->SetVisible(false);
                m_TowerState = TowerState::MOVING;
            }
        }
    }

    //END
    else if (m_Scene == Scene::END) {
        if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
            m_SceneManager->StartScene();
            m_Player->ResetData();
            m_Scene = Scene::START;
        }
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
