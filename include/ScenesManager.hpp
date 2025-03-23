#ifndef SCENESMANAGER_HPP
#define SCENESMANAGER_HPP

#include <memory>
#include <vector>

#include "BackgroundImage.hpp"
#include "AnimationObject.hpp"
#include "TextObject.hpp"
#include "Player.hpp"

#include "Util/GameObject.hpp"

class ScenesManager {
public:
    ScenesManager();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return {m_BackGround, m_Loading, m_Story, m_Remind, m_Title};
    }

    // Loading
    [[nodiscard]] std::shared_ptr<AnimationObject> GetLoading() const { return m_Loading; }

    //Story相關函數
    void StartStory () {
        m_Story->SetVisible(true);
        m_Remind->SetVisible(true);
    }

    void EndStory () {
        m_Story->SetVisible(false);
        m_Remind->SetVisible(false);
        m_Title->SetVisible(true);
    }

    void NextScene();

private:
    std::shared_ptr<BackgroundImage> m_BackGround;

    std::shared_ptr<AnimationObject> m_Loading;
    std::shared_ptr<TextObject> m_Story;
    std::shared_ptr<TextObject> m_Remind;
    std::shared_ptr<TextObject> m_Title;

    std::shared_ptr<Player> m_Player;

    int m_scene = 0;
};

#endif
