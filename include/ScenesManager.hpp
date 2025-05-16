#ifndef SCENESMANAGER_HPP
#define SCENESMANAGER_HPP

#include <MapManager.hpp>
#include <memory>
#include <vector>

#include "BackgroundImage.hpp"
#include "AnimationObject.hpp"
#include "ImageObject.hpp"
#include "TextObject.hpp"
#include "Player.hpp"


#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"

class ScenesManager {
public:
    ScenesManager(const std::shared_ptr<MapManager> &mapManager, const std::shared_ptr<Player> &player);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> children;
        children.push_back(m_BackGround);
        children.push_back(m_Loading);
        children.insert(children.end(), m_StorySceneChildren.begin(), m_StorySceneChildren.end());
        children.insert(children.end(), m_TowerSceneChildren.begin(), m_TowerSceneChildren.end());
        children.insert(children.end(), m_EndSceneChildren.begin(), m_EndSceneChildren.end());
        return children;
    }

    // Loading
    [[nodiscard]] std::shared_ptr<AnimationObject> GetLoading() const { return m_Loading; }

    //Story相關函數
    void StartStory () const {
        for (auto &child : m_StorySceneChildren)
            child->SetVisible(true);
    }

    void EndStory () const {
        for (auto &child : m_StorySceneChildren)
            child->SetVisible(false);
        for (auto &child : m_TowerSceneChildren)
            child->SetVisible(true);
    }

    // ResetText
    void ResetFloor (int courrentfloor) const;
    void ResetPlayerStatus()  const;
    void ResetPlayerLevel() const;
    void ResetPlayerHP() const;
    void ResetPlayerATK() const;
    void ResetPlayerDEF() const;
    void ResetPlayerAGI() const;
    void ResetPlayerEXP() const;
    void ResetPlayerYellowKey() const;
    void ResetPlayerBlueKey() const;
    void ResetPlayerRedKey() const;
    void ResetPlayerCoins() const;

    void StartScene();
    void NextScene();
    void EndScene(bool is_win) const;
    void SetEndSceneVisible(bool visible) const;

private:
    std::shared_ptr<BackgroundImage> m_BackGround;
    std::shared_ptr<AnimationObject> m_Loading;
    // Story
    std::shared_ptr<TextObject> m_Story;
    std::shared_ptr<TextObject> m_StoryRemind;
    std::vector<std::shared_ptr<Util::GameObject>> m_StorySceneChildren;

    // 樓層顯示
    std::vector<std::string> m_Floortext;
    std::shared_ptr<TextObject> m_Floor;
    std::shared_ptr<ImageObject> m_PlayerImage;
    std::shared_ptr<TextObject> m_PlayerStatus;
    std::shared_ptr<TextObject> m_PlayerLevel;
    std::shared_ptr<TextObject> m_PlayerHP;
    std::shared_ptr<TextObject> m_PlayerATK;
    std::shared_ptr<TextObject> m_PlayerDEF;
    std::shared_ptr<TextObject> m_PlayerAGI;
    std::shared_ptr<TextObject> m_PlayerEXP;
    std::shared_ptr<TextObject> m_PlayerYellowKey;
    std::shared_ptr<TextObject> m_PlayerBlueKey;
    std::shared_ptr<TextObject> m_PlayerRedKey;
    std::shared_ptr<TextObject> m_PlayerCoins;
    std::vector<std::shared_ptr<Util::GameObject>> m_TowerSceneChildren;

    // End顯示
    std::shared_ptr<ImageObject> m_EndScene;
    std::shared_ptr<TextObject> m_EndText;
    std::shared_ptr<TextObject> m_EndReminder;
    std::vector<std::shared_ptr<Util::GameObject>> m_EndSceneChildren;

    std::shared_ptr<MapManager> m_MapManager;
    std::shared_ptr<Player> m_Player;

    int m_scene = 0;
};

#endif
