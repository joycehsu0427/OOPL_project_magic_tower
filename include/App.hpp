#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"

#include "ScenesManager.hpp"
#include "MapManager.hpp"
#include "Player.hpp"
#include "TextObject.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "Road.hpp"

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

    State m_CurrentState = State::START;

    Scene m_Scene = Scene::START;

    Util::Renderer m_Renderer;

    std::shared_ptr<ScenesManager> m_SceneManager;
    std::shared_ptr<MapManager> m_MapManager;
    // std::shared_ptr<TextObject> m_Text;

    std::shared_ptr<Player> m_Player;

    // std::shared_ptr<Enemy> m_Enemy;
    // std::shared_ptr<Item> m_Item;
    std::shared_ptr<Road> m_Road;

};

#endif
