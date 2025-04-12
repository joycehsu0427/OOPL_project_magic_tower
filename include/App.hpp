#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"

#include "ScenesManager.hpp"
#include "MapManager.hpp"
#include "Player.hpp"
#include "ItemDialog.hpp"
#include "NPCDialog.hpp"
#include "Fighting.hpp"
#include "ShopDialog.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    enum class Scene {
        START,
        STORY,
        TOWER,
        DEAD,
        WIN
    };

    enum class TowerState {
        MOVING,
        ENEMYFIGHTING,
        ITEMDIALOG,
        NPCDIALOG,
        DOOROPEN,
        STAIRMOVING,
        SHOPDIALOG,
        FLYING
    };

    State m_CurrentState = State::START;

    Scene m_Scene = Scene::START;

    TowerState m_TowerState = TowerState::MOVING;

    Util::Renderer m_Renderer;

    std::shared_ptr<ScenesManager> m_SceneManager;
    std::shared_ptr<MapManager> m_MapManager;

    std::shared_ptr<Player> m_Player;

    std::shared_ptr<ItemDialog> m_ItemDialog;
    std::shared_ptr<NPCDialog> m_NPCDialog;
    std::shared_ptr<ShopDialog> m_ShopDialog;
    std::shared_ptr<Fighting> m_Fighting;
    int m_FightingTimer = 0;

};

#endif
