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
#include "Fly.hpp"
#include "EnemyDataManager.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

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
        FLYING,
        EnemyData
    };

    State m_CurrentState = State::START;

    Scene m_Scene = Scene::START;

    TowerState m_TowerState = TowerState::MOVING;

    Util::Renderer m_Renderer;

    std::shared_ptr<ScenesManager> m_SceneManager;
    std::shared_ptr<MapManager> m_MapManager;

    std::shared_ptr<Player> m_Player;

    // 戰鬥畫面
    std::shared_ptr<Fighting> m_Fighting;
    int m_FightingTimer = 0;

    // Dialog
    std::shared_ptr<ItemDialog> m_ItemDialog;
    std::shared_ptr<NPCDialog> m_NPCDialog;
    std::shared_ptr<ShopDialog> m_ShopDialog;

    // 樓層飛行
    std::shared_ptr<Fly> m_Fly;
    // 怪物數據顯示
    std::shared_ptr<EnemyDataManager> m_EnemyDataManager;
};

#endif
